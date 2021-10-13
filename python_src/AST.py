from pysmt.shortcuts import And, Or, Not, Symbol, TRUE, FALSE, is_sat, Array, GE, LT
from pysmt.shortcuts import Solver, simplify, Int, FreshSymbol, Plus, Store, Select
from pysmt.shortcuts import LE, LT
from pysmt.typing import INT
from State import State, Frame
from Mappings import YVR_BUILTIN_OP_TO_PYSMT

class Program:
    def __init__(self, statements = [], variables = {}, labels = {}, functions={}):
        self.statements = statements
        self.current_line = len(statements)
        self.labels = labels
        self.variables = variables
        self.functions = functions

    def append(self, statement, label = None):
        if label:
            self.labels[label] = self.current_line
        self.statements.append(statement)
        self.current_line += 1

class Expression:
    pass

class AtomicExpression(Expression):
    pass

class Variable(AtomicExpression):
    def __init__(self, name):
        self.name = name

    def eval(self, state):
        return state.get_variable(self.name)

class RecordIndexExpression(Expression):
    def __init__(self, record, element):
        self.record = record
        self.element = element

    def eval(self, state):
        return state.get_variable(self.record)[self.element]

class Value(AtomicExpression):
    def __init__(self, value):
        self.value = value

    def eval(self, state):
        return self.value

class UniqueSymbol(Value):
    def __init__(self, type):
        self.type = type

    def eval(self, state):
        return FreshSymbol(self.type)

class UnaryExpression(Expression):
    def __init__(self, op, arg):
        self.op = op
        self.arg = arg

    def eval(self, state):
        return self.op(self.arg.eval(state))

class BinaryExpression(Expression):
    def __init__(self, lhs, op, rhs):
        self.lhs = lhs
        self.op = op
        self.rhs = rhs

    def eval(self, state):
        return self.op(self.lhs.eval(state), self.rhs.eval(state))

class TernaryExpression(Expression):
    def __init__(self, op, first, second, third):
        self.op = op
        self.first = first
        self.second = second
        self.third = third

    def eval(self, state):
        return self.op(self.first.eval(state), self.second.eval(state), self.third.eval(state))

class ArrayIndexExpression(Expression):
    def __init__(self, arr, index):
        self.arr = arr
        self.index = index

    def eval(self, state):
        return Select(self.arr.eval(state), self.index.eval(state))

array_to_length_map = dict()

class NewArrayExpression(Expression):
    def __init__(self, default, length=None):
        self.default = default
        self.length = length

    def eval(self, state):
        arr = Array(INT, self.default.eval(state))
        if self.length:
            array_to_length_map[arr] = self.length
        return arr

class Function:
    def __init__(self, name, params, variables, statements, labels):
        self.name = name
        self.params = params
        self.variables = variables
        self.variables.update(params)
        self.statements = statements
        self.labels = labels

    def __str__(self):
        return f"define {self.name}({', '.join(self.params)}): {', '.join(self.variables)}"

class Statement:
    def exec(self, state):
        return state.advance_pc()

class Return(Statement):
    def __init__(self, expression):
        self.expression = expression

    def exec(self, state):
        state.pop_frame(self.expression.eval(state))
        return [state]

class Assignment(Statement):
    def __init__(self, target, expression):
        self.target = target
        self.expression = expression

    def exec(self, state):
        if isinstance(self.target, ArrayIndexExpression):
            index = self.target.index.eval(state)
            arr = self.target.arr.eval(state)
            state.assign_variable(self.target.arr.name, Store(arr, index, self.expression.eval(state)))
            if arr in array_to_length_map:
                state.path_cond = And(state.path_cond, And(GE(index, Int(0)), LT(index, Int(array_to_length_map[arr]))))
        elif isinstance(self.target, RecordIndexExpression):
            state.get_variable(self.target.record)[self.target.element] = self.expression.eval(state)
        else:
            state.assign_variable(self.target.name, self.expression.eval(state))
        return [state.advance_pc()]

class Record:
    def __init__(self, name, elements):
        self.name = name
        self.elements = elements

    def __str__(self):
        return f"{self.name}({', '.join(self.elements.items())})"

class FunctionCallAndAssignment(Statement):
    def __init__(self, target, function, arguments):
        self.target = target
        self.function = function
        self.arguments = arguments

    def exec(self, state):

        if self.function in YVR_BUILTIN_OP_TO_PYSMT:
            arguments = []
            for argument in self.arguments:
                arguments.append(argument.eval(state))
            if isinstance(self.target, ArrayIndexExpression):
                state.assign_variable(self.target.arr.name,
                                      Store(self.target.arr.eval(state), self.target.index.eval(state),
                                            YVR_BUILTIN_OP_TO_PYSMT[self.function](*arguments)))
            else:
                state.assign_variable(self.target.name, YVR_BUILTIN_OP_TO_PYSMT[self.function](*arguments))
            return [state.advance_pc()]


        function = state.frame_stack[0].function.functions[self.function]

        arguments = []
        for argument in self.arguments:
            arguments.append(argument.eval(state))

        state.advance_pc()
        state.push_frame(Frame(function, 0, function.variables, self.target))
        for i, param in enumerate(function.params):
            state.assign_variable(param, arguments[i])
        return [state]

class ConditionalBranch(Statement):
    def __init__(self, condition, dest):
        self.condition = condition
        self.dest = dest

    def exec(self, state):
        return state.split(self.condition.eval(state), state.head_frame().function.labels[self.dest])

class UnconditionalBranch(ConditionalBranch):
    def __init__(self, dest):
        self.dest = dest
    def exec(self, state):
        return [state.update_pc(state.head_frame().function.labels[self.dest])]
