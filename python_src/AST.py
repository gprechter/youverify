from pysmt.shortcuts import And, Or, Not, Symbol, TRUE, FALSE, is_sat, Array, GE, LT, Equals
from pysmt.shortcuts import Solver, simplify, Int, FreshSymbol, Plus, Store, Select, BV
from pysmt.shortcuts import LE, LT, get_model
from pysmt.typing import INT, BVType, BOOL, ArrayType, _BVType
from State import State, Frame
from copy import copy
from Mappings import YVR_BUILTIN_OP_TO_PYSMT
from TypeCheckingRules import both_same, unary_type_checking_rules, binary_type_checking_rules, both_records_or_null, builtin_type_checking_rules
from pysmt.type_checker import SimpleTypeChecker
from pysmt.fnode import FNode

class Program:
    def __init__(self, statements = [], variables = {}, labels = {}, functions={}):
        self.statements = statements
        self.current_line = len(statements)
        self.labels = labels
        self.variables = variables
        self.functions = functions


class TCContext:
    def __init__(self, variables, functions, return_type = None):
        self.variables = variables
        self.functions = functions
        self.return_type = return_type
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

    def type_check(self, context):
        return context.variables[self.name], ""

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
            rec = State.records[state.get_variable_type(self.record)]
            for k, v in zip(rec.elements, rec.types):
                if isinstance(v, str):
                    symb_elems[k] = Symbol(f"{address.symbol_name()}_{k}", BVType(32))
                else:
                    symb_elems[k] = Symbol(f"{address.symbol_name()}_{k}", INT)
            state.addr_map[concrete_address] = symb_elems
            return state.addr_map[concrete_address][self.element]

    def type_check(self, context):
        rec_type = context.variables[self.record]
        record = State.records[rec_type]
        return record.types[record.elements.index(self.element)], ""


class Value(AtomicExpression):
    def __init__(self, value, type):
        self.value = value
        self.type = type

    def eval(self, state):
        return self.value

    def type_check(self, context):
        return self.type, ""

    def __repr__(self):
        return f"{self.value}"

class YouVerifyArray:
    def __init__(self, default_value=0, length=None, array=None, index=Int(0)):
        self.default_value = default_value
        self.length = length
        self.index = index
        if array:
            self._array = array
        else:
            self._array = [Array(INT, default_value)]

    def get_array(self):
        return self._array[0]

    def set_array(self, array):
        self._array[0] = array

    def __repr__(self):
        return f"{[simplify(self.get_array().array_value_get(Int(i))) for i in range(simplify(self.length).constant_value())]}"

class UniqueSymbol(Value):
    def __init__(self, type):
        self.type = type

    def type_check(self, context):
        return self.type, ""

    def eval(self, state):
        return FreshSymbol(self.type)

class UnaryExpression(Expression):
    def __init__(self, op, op_name, arg):
        self.op = op
        self.op_name = op_name
        self.arg = arg

    def type_check(self, context):
        comp_func, type = unary_type_checking_rules[self.op_name]
        operand = self.arg.type_check(context)
        if operand[1]:
            return operand
        return type, "" if comp_func(operand[0]) else f"{self.op_name} is being used on the incorrect operand."

    def eval(self, state):
        return self.op(self.arg.eval(state))

class BinaryExpression(Expression):
    def __init__(self, lhs, op, op_name, rhs):
        self.lhs = lhs
        self.op = op
        self.op_name = op_name
        self.rhs = rhs

    def eval(self, state):
        lhs = self.lhs.eval(state)
        rhs = self.rhs.eval(state)
        if isinstance(lhs, YouVerifyArray):
            return YouVerifyArray(lhs.default_value, lhs.length, lhs._array, self.op(lhs.index, rhs))
        return self.op(lhs, rhs)

    def type_check(self, context):
        comp_func, type = binary_type_checking_rules[self.op_name]
        lhs = self.lhs.type_check(context)
        rhs = self.rhs.type_check(context)
        if lhs[1]:
            return lhs
        if rhs[1]:
            return rhs
        return type, "" if comp_func(lhs[0], rhs[0]) else f"{self.op_name} is being used on the incorrect operands."

    def __repr__(self):
        return f"{self.lhs} {self.op} {self.rhs}"

class TernaryExpression(Expression):
    def __init__(self, op, first, second, third):
        self.op = op
        self.first = first
        self.second = second
        self.third = third

    def type_check(self, context):
        f, s, t = self.first.type_check(context), self.second.type_check(context), self.third.type_check(context)
        f_type, f_err = f
        s_type, s_err = s
        t_type, t_err = t
        if f_err:
            return f_type, f_err
        if s_err:
            return s_type, s_err
        if t_err:
            return t_type, t_err
        return s_type, "" if (f_type == BOOL and (both_records_or_null(s_type, t_type) or both_same(s_type, t_type))) else "The types were incorrect."

    def eval(self, state):
        return self.op(self.first.eval(state), self.second.eval(state), self.third.eval(state))

class ArrayIndexExpression(Expression):
    def __init__(self, arr, index):
        self.arr = arr
        self.index = index

    def type_check(self, context):
        arr_type, err = self.arr.type_check(context)
        if err:
            return arr_type, err
        return arr_type.elem_type, ""

    def eval(self, state):
        arr = self.arr.eval(state)
        index = self.index.eval(state)
        return Select(arr.get_array(), index)

    def __repr__(self):
        return f"{self.arr}[{self.index}]"

array_to_length_map = dict()

class NewArrayExpression(Expression):
    def __init__(self, default, length=None):
        self.default = default
        self.length = length

    def type_check(self, context):
        default_type, err = self.default.type_check(context)
        if err:
            return default_type, err
        return ArrayType(INT, (BVType(32) if isinstance(default_type, str) and default_type == 'null' else default_type)), ""

    def eval(self, state):
        arr = YouVerifyArray(self.default.eval(state), Int(self.length))
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

    def type_check(self, context):
        if self.expression == None and context.return_type == None:
            return None, ""
        elif self.expression == None or context.return_type == None:
            return None, "A function with no return type cannot return a value, and a function with a return type must have a return value."
        return_expr_type, err = self.expression.type_check(context)
        if err:
            return return_expr_type, err
        return None, "" if return_expr_type == context.return_type else "The return expression type must match the function's return type"

    def exec(self, state):
        if self.expression:
            state.pop_frame(self.expression.eval(state))
        else:
            state.pop_frame(self.expression)
        return [state]

class Assume(Statement):
    def __init__(self, expression):
        self.expression = expression

    def type_check(self, context):
        cond_type, err = self.expression.type_check(context)
        if err:
            return cond_type, err
        return None, "" if cond_type == BOOL else "The condition to a conditional branch must be a boolean value."

    def exec(self, state):
        state.path_cond = And(state.path_cond, self.expression.eval(state))
        return [state.advance_pc()]

class Assert(Statement):
    def __init__(self, expression):
        self.expression = expression

    def type_check(self, context):
        cond_type, err = self.expression.type_check(context)
        if err:
            return cond_type, err
        return None, "" if cond_type == BOOL else "The condition to a conditional branch must be a boolean value."


    def exec(self, state):
        if is_sat(And(state.path_cond, Not(self.expression.eval(state)))):
            state.path_cond = FALSE()
            return [state]
        else:
            return [state.advance_pc()]

class Pointer_Dereference_Expression(Expression):
    def __init__(self, name):
        self.name = name

    def eval(self, state):
        variable = state.get_variable(self.name)
        state.path_cond = And(state.path_cond, GE(variable.index, Int(0)), LT(variable.index, variable.length))
        return Select(variable.get_array(), variable.index)

class Alloc_Concrete(Statement):
    def __init__(self, target, record, arguments):
        self.target = target
        self.record = record
        self.arguments = arguments

    def type_check(self, context):
        target, target_issue = self.target.type_check(context)
        record = State.records[self.record]
        if len(self.arguments) != len(record.elements):
            return None, f"There must be {len(record.elements)} values to initialize the {self.record} record."
        for t, e in zip(record.types, self.arguments):
            elem_t, err = e.type_check(context)
            if err:
                return None, err
            if not(both_records_or_null(elem_t, t) or both_same(elem_t, t)):
                return None, f"The expression {e} is the incorrect type for the given element, {t}."
        if target_issue:
            return target, target_issue
        return None, "" if both_records_or_null(target, self.record) else "The record must be assigned to the same type."

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

    def type_check(self, context):
        target, target_issue = self.target.type_check(context)
        if target_issue:
            return target, target_issue
        return None, "" if target == self.record else "The type of a symbolic record must match the target."

    def exec(self, state):
        state.assign_variable(self.target.name, Symbol(f"{self.record}_{self.target.name}", BVType(32)))
        return [state.advance_pc()]

class NULL(AtomicExpression):

    def type_check(self, context):
        return 'null', ""

    def eval(self, state):
        return BV(0, 32)

class Assignment(Statement):
    def __init__(self, target, expression):
        self.target = target
        self.expression = expression

    def exec(self, state):
        if isinstance(self.target, ArrayIndexExpression):
            index = self.target.index.eval(state)
            arr = self.target.arr.eval(state)
            arr.set_array(Store(arr.get_array(), index, self.expression.eval(state)))
            if arr.length:
                state.path_cond = And(state.path_cond, And(GE(index, Int(0)), LT(index, arr.length)))
        elif isinstance(self.target, RecordIndexExpression):
            address = simplify(state.get_variable(self.target.record))
            state.addr_map[address.constant_value()][self.target.element] = self.expression.eval(state)
        elif isinstance(self.target, Pointer_Dereference_Expression):
            ref = state.get_variable(self.target.name)
            state.path_cond = And(state.path_cond, GE(ref.index, Int(0)), LT(ref.index, ref.length))
            if not is_sat(state.path_cond):
                assert False, "OVERFLOW!"
            ref.set_array(Store(ref.get_array(), ref.index, self.expression.eval(state)))
        else:
            if isinstance(state.get_variable(self.target.name), YouVerifyArray):
                ref = state.get_variable(self.target.name)
                val = copy(self.expression.eval(state))
                if isinstance(val, FNode) and val.is_symbol():
                    ref.index = val
                else:
                    state.assign_variable(self.target.name, val)
            else:
                state.assign_variable(self.target.name, self.expression.eval(state))
        return [state.advance_pc()]

    def type_check(self, context):
        target, target_issue = self.target.type_check(context)
        value, value_issue = self.expression.type_check(context)
        if value_issue or target_issue:
            return None, f"{value_issue}, {target_issue}"
        return None, "" if both_records_or_null(target, value) or both_same(target, value) else f"Target {target} and value {value} types must match."

    def __repr__(self):
        return f"{repr(self.target)} = {repr(self.expression)}"

class Record:
    def __init__(self, name, elements, types):
        self.name = name
        self.elements = elements
        self.types = types

    def __str__(self):
        return f"{self.name}({', '.join(self.elements)})"

def wrap_target_var(var):
    def return_to_var(state, value):
        state.assign_variable(var.name, value)
    return return_to_var

def wrap_target_arr_index(arr, index):
    def return_to_arr_index(state, value):
        i = index.eval(state)
        a = arr.eval(state)
        a.set_array(Store(a.get_array(), i, value))
        if a.length:
            state.path_cond = And(state.path_cond, And(GE(i, Int(0)), LT(i, a.length)))
    return return_to_arr_index

class FunctionCallAndAssignment(Statement):
    def __init__(self, target, function, arguments):
        self.target = target
        self.function = function
        self.arguments = arguments

    def type_check(self, context):
        if self.function in builtin_type_checking_rules:
            type_check_func, return_type_func, num_args = builtin_type_checking_rules[self.function]
            if self.function == 'extract':
                return_type_func = lambda bv, s, e: BVType(1 + self.arguments[2].eval(None).constant_value() - self.arguments[1].eval(None).constant_value())
        else:
            type_check_func = lambda *args: all([a == p.name for a, p in zip(args, context.functions[self.function].params.values())])
            return_type_func = lambda *args: context.functions[self.function].return_value
            num_args = len(context.functions[self.function].params)
        if num_args != len(self.arguments):
            return None, "The number of arguments allowed and the number present are not the same!"
        args = [arg.type_check(context) for arg in self.arguments]
        for type, err in args:
            if err:
                return None, err
        if not type_check_func(*[arg[0] for arg in args]):
            return None, "The arguments to the function are of the wrong type."
        return_type = return_type_func(*[arg[0] for arg in args])
        target, target_issue = self.target.type_check(context)
        if target_issue:
            return None, target_issue
        if not return_type:
            return None, "Return type must not be NONE."
        return None, "" if both_same(target, return_type) or both_records_or_null(target, return_type) else f"Target {target} and value {return_type} types must match."


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
            state.assign_variable(param, copy(arguments[i]))
        return [state]

class FunctionCallWithNoAssignment(Statement):
    def __init__(self, function, arguments):
        self.function = function
        self.arguments = arguments

    def type_check(self, context):
        if self.function in builtin_type_checking_rules:
            return None, "Builtins can never be called with a target."
        else:
            type_check_func = lambda *args: all([a == p.name for a, p in zip(args, context.functions[self.function].params.values())])
            return_type_func = lambda *args: context.functions[self.function].return_value
            num_args = len(context.functions[self.function].params)
        if num_args != len(self.arguments):
            return None, "The number of arguments allowed and the number present are not the same!"
        args = [arg.type_check(context) for arg in self.arguments]
        print(args)
        for type, err in args:
            if err:
                return None, err
        if not type_check_func(*[arg[0] for arg in args]):
            return None, "The arguments to the function are of the wrong type."

        return None, ""



    def exec(self, state):

        if self.function in YVR_BUILTIN_OP_TO_PYSMT:
            assert False, "Builtins can never be called without a target."

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

    def type_check(self, context):
        cond_type, err = self.condition.type_check(context)
        if err:
            return cond_type, err
        return None, "" if cond_type == BOOL else "The condition to a conditional branch must be a boolean value."

    def exec(self, state):
        return state.split(self.condition.eval(state), state.head_frame().function.labels[self.dest])

    def __repr__(self):
        return f"if {self.condition} goto {self.dest}"

class UnconditionalBranch(ConditionalBranch):
    def __init__(self, dest):
        self.dest = dest
    def exec(self, state):
        return [state.update_pc(state.head_frame().function.labels[self.dest])]

    def type_check(self, context):
        return None, ""

    def __repr__(self):
        return f"goto {self.dest}"
