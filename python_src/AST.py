from pysmt.shortcuts import And, Or, Not, Symbol, TRUE, FALSE, is_sat, Array, GE, LT, Equals
from pysmt.shortcuts import Solver, simplify, Int, FreshSymbol, Plus, Store, Select, BV
from pysmt.shortcuts import LE, LT
from pysmt.typing import INT, BVType
from State import State, Frame
from Mappings import YVR_BUILTIN_OP_TO_PYSMT
from pyeda.inter import *

class Program:
    def __init__(self, statements = [], variables = {}, labels = {}, functions={}):
        self.statements = statements
        self.current_line = len(statements)
        self.labels = labels
        self.variables = variables
        self.functions = functions

'''
    def append(self, statement, label = None):
        if label:
            self.labels[label] = self.current_line
        self.statements.append(statement)
        self.current_line += 1
'''

class Expression:
    pass

class AtomicExpression(Expression):
    pass

class Variable(AtomicExpression):
    def __init__(self, name):
        self.name = name

    def eval(self, state):
        return state.get_variable(self.name)

    def type_check(self, program):
        return program.variables[self.name].name, ""

    def __repr__(self):
        return f"{self.name}"

class RecordIndexExpression(Expression):
    def __init__(self, record, element):
        self.record = record
        self.element = element

    def eval(self, state):
        address = simplify(state.get_variable(self.record))
        if address.is_constant():
            return state.addr_map[address.constant_value()][self.element]
        else:
            if address.symbol_name() not in state.concrete_symbolic_pointers:
                concrete_address = state.base_addr
                state.path_cond = And(state.path_cond, Equals(address, BV(concrete_address, 32)))
                state.concrete_symbolic_pointers[address.symbol_name()] = concrete_address
                state.base_addr = state.base_addr + 1
            else:
                concrete_address = state.concrete_symbolic_pointers[address.symbol_name()]
            symb_elems ={}
            for k, v in State.records[state.get_variable_type(self.record)].elements.items():
                if isinstance(v.name, str):
                    symb_elems[k] = Symbol(f"{address.symbol_name()}_{k}", BVType(32))
                else:
                    symb_elems[k] = Symbol(f"{address.symbol_name()}_{k}", INT)
            state.addr_map[concrete_address] = symb_elems
            return state.addr_map[concrete_address][self.element]

class Value(AtomicExpression):
    def __init__(self, value, type):
        self.value = value
        self.type = type

    def eval(self, state):
        fake = bddvar('fake')
        return [[fake.restrict({fake: 1}), self.value]]

    def type_check(self, program):
        return self.type, ""

    def __repr__(self):
        return f"{self.value}"

class YouVerifyArray:
    def __init__(self, default_value=0, length=None, array=None):
        self.length = length
        if array:
            self.array = array
        else:
            self.array = Array(INT, default_value)

    def __copy__(self):
        return YouVerifyArray(self.default_value, self.length, self.array)

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
        lhs = self.lhs.eval(state)
        rhs = self.rhs.eval(state)
        new_vs = []
        for lvs in lhs:
            for rvs in rhs:
                new_vs.append([lvs[0] & rvs[0], self.op(lvs[1], rvs[1])])
        return new_vs

    def type_check(self, program):
        return

    def __repr__(self):
        return f"{self.lhs} {self.op} {self.rhs}"

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
        arr = self.arr.eval(state)
        index = self.index.eval(state)
        if arr.length:
            state.path_cond = And(state.path_cond, And(GE(index, Int(0)), LT(index, Int(arr.length))))
        return Select(arr.array, index)

    def __repr__(self):
        return f"{self.arr}[{self.index}]"

array_to_length_map = dict()

class NewArrayExpression(Expression):
    def __init__(self, default, length=None):
        self.default = default
        self.length = length

    def eval(self, state):
        arr = YouVerifyArray(self.default.eval(state), self.length)
        return arr

class Function:
    def __init__(self, name, params, variables, statements, labels, return_value):
        self.name = name
        self.params = params
        self.variables = variables
        self.variables.update(params)
        self.statements = statements
        self.labels = labels
        self.return_value = return_value

    def __str__(self):
        return f"define {self.name}({', '.join(self.params)}): {', '.join(self.variables)}"

class Statement:
    def exec(self, state):
        return state.advance_pc()

class Return(Statement):
    def __init__(self, expression):
        self.expression = expression

    def exec(self, state):
        if self.expression:
            state.pop_frame(self.expression.eval(state))
        else:
            state.pop_frame(self.expression)
        return [state]

class Assume(Statement):
    def __init__(self, expression):
        self.expression = expression

    def exec(self, state):
        state.path_cond = And(state.path_cond, self.expression.eval(state))
        return [state.advance_pc()]

class Assert(Statement):
    def __init__(self, expression):
        self.expression = expression

    def exec(self, state):
        if is_sat(And(state.path_cond, Not(self.expression.eval(state)))):
            state.path_cond = FALSE()
            return [state]
        else:
            return [state.advance_pc()]

class Alloc_Concrete(Statement):
    def __init__(self, target, record, arguments):
        self.target = target
        self.record = record
        self.arguments = arguments

    def exec(self, state):
        address = state.base_addr
        arguments = [arg.eval(state) for arg in self.arguments]
        state.addr_map[address] = {k: v for k, v in zip(State.records[self.record].elements, arguments)}
        state.base_addr = state.base_addr + 1
        state.assign_variable(self.target.name, BV(address, 32))
        return [state.advance_pc()]

class Alloc_Symbolic(Statement):
    def __init__(self, target, record):
        self.target = target
        self.record = record

    def exec(self, state):
        state.assign_variable(self.target.name, Symbol(f"{self.record}_{self.target.name}", BVType(32)))
        return [state.advance_pc()]

class Assignment(Statement):
    def __init__(self, target, expression):
        self.target = target
        self.expression = expression

    def exec(self, state):
        if isinstance(self.target, ArrayIndexExpression):
            index = self.target.index.eval(state)
            arr = self.target.arr.eval(state)
            arr.array = Store(arr.array, index, self.expression.eval(state))
            state.assign_variable(self.target.arr.name, arr)
            if arr.length:
                state.path_cond = And(state.path_cond, And(GE(index, Int(0)), LT(index, Int(arr.length))))
        elif isinstance(self.target, RecordIndexExpression):
            address = simplify(state.get_variable(self.target.record))
            state.addr_map[address.constant_value()][self.target.element] = self.expression.eval(state)
        else:
            state.assign_variable(self.target.name, self.expression.eval(state))
        return state.advance_pc()

    def type_check(self, program):
        target, target_issue = self.target.type_check(program)
        value, value_issue = self.expression.type_check(program)
        if value_issue or target_issue:
            return None, f"{value_issue}, {target_issue}"
        return None, f"Target {target} and value {value} types must match." if target == value else ""

    def __repr__(self):
        return f"{repr(self.target)} = {repr(self.expression)}"

class Record:
    def __init__(self, name, elements):
        self.name = name
        self.elements = elements

    def __str__(self):
        return f"{self.name}({', '.join(self.elements.items())})"

def wrap_target_var(var):
    def return_to_var(state, value):
        state.assign_variable(var.name, value)
    return return_to_var

def wrap_target_arr_index(arr, index):
    def return_to_arr_index(state, value):
        i = index.eval(state)
        a = arr.eval(state)
        a.array = Store(a.array, i, value)
        if a.length:
            state.path_cond = And(state.path_cond, And(GE(i, Int(0)), LT(i, Int(a.length))))
    return return_to_arr_index

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
        wrapped_target = wrap_target_arr_index(self.target.arr, self.target.index)\
            if isinstance(self.target, ArrayIndexExpression) else wrap_target_var(self.target)
        state.push_frame(Frame(function, 0, {k: [v.name, None] for k, v in function.variables.items()}, wrapped_target))
        for i, param in enumerate(function.params):
            state.assign_variable(param, arguments[i])
        return [state]

class FunctionCallWithNoAssignment(Statement):
    def __init__(self, function, arguments):
        self.function = function
        self.arguments = arguments

    def exec(self, state):

        if self.function in YVR_BUILTIN_OP_TO_PYSMT:
            assert False, "Builtins can never be called with a target."

        function = state.frame_stack[0].function.functions[self.function]

        arguments = []
        for argument in self.arguments:
            arguments.append(argument.eval(state))

        state.advance_pc()
        state.push_frame(Frame(function, 0, {k: [v.name, None] for k, v in function.variables.items()}, None))
        for i, param in enumerate(function.params):
            state.assign_variable(param, arguments[i])
        return [state]

class ConditionalBranch(Statement):
    def __init__(self, condition, dest):
        self.condition = condition
        self.dest = dest

    def exec(self, state):
        return state.split(self.condition.eval(state), state.head_frame().function.labels[self.dest])

    def __repr__(self):
        return f"if {self.condition} goto {self.dest}"

class UnconditionalBranch(ConditionalBranch):
    def __init__(self, dest):
        self.dest = dest
    def exec(self, state):
        return [state.update_pc(state.head_frame().function.labels[self.dest])]

    def __repr__(self):
        return f"goto {self.dest}"
