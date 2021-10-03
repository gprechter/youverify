from pysmt.shortcuts import And, Or, Not, Symbol, TRUE, FALSE, is_sat, Array
from pysmt.shortcuts import Solver, simplify, Int, FreshSymbol, Plus, Store, Select
from pysmt.shortcuts import LE, LT
from pysmt.typing import INT

class Program:
    def __init__(self, statements = [], variables = {}, labels = {}):
        self.statements = statements
        self.current_line = len(statements)
        self.labels = labels
        self.variables = variables

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
        return state.variables[self.name]

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

class NewArrayExpression(Expression):
    def __init__(self, default):
        self.default = default

    def eval(self, state):
        return Array(INT, self.default.eval(state))

class Function:
    def __init__(self, name, params, vars, statements, labels):
        self.name = name
        self.params = params
        self.local_variables = vars
        self.local_variables.update(params)
        self.statements = statements
        self.labels = labels

    def __str__(self):
        return f"define {self.name}({', '.join(self.params)}): {', '.join(self.local_variables)}"

class Statement:
    def exec(self, state):
        return state.advance_pc()

class Return(Statement):
    def __init__(self, expression):
        self.expression = expression

    def exec(self, state):
        return [state]

class Assignment(Statement):
    def __init__(self, target, expression):
        self.target = target
        self.expression = expression

    def exec(self, state):
        if isinstance(self.target, ArrayIndexExpression):
            state.variables[self.target.arr.name] = Store(self.target.arr.eval(state), self.target.index.eval(state), self.expression.eval(state))
        else:
            state.variables[self.target.name] = self.expression.eval(state)
        return [state.advance_pc()]

class FunctionCallAndAssignment(Statement):
    def __init__(self, target, function, arguments):
        self.target = target
        self.function = function
        self.arguments = arguments



class ConditionalBranch(Statement):
    def __init__(self, condition, dest):
        self.condition = condition
        self.dest = dest

    def exec(self, state):
        return state.split(self.condition.eval(state), state.program.labels[self.dest])

class UnconditionalBranch(ConditionalBranch):
    def __init__(self, dest):
        self.dest = dest
    def exec(self, state):
        return [state.update_pc(state.program.labels[self.dest])]
