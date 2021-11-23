from pysmt.shortcuts import And, Or, Not, Symbol, TRUE, FALSE, is_sat, Array, GE, LT, Equals
from pysmt.shortcuts import Solver, simplify, Int, FreshSymbol, Plus, Store, Select, BV
from pysmt.shortcuts import LE, LT, get_model
from pysmt.typing import INT, BVType, BOOL, ArrayType, _BVType
from State import Frame, PathConstraint
from copy import copy
from Mappings import YVR_BUILTIN_OP_TO_PYSMT
from TypeCheckingRules import both_same, unary_type_checking_rules, binary_type_checking_rules, both_records_or_null, builtin_type_checking_rules
from pysmt.type_checker import SimpleTypeChecker
from pysmt.fnode import FNode
from YouVerifyArray import YouVerifyArray

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
            return state.current_state.addr_map[address.constant_value()][self.element]
        else:
            if address.symbol_name() not in state.current_state.concrete_symbolic_pointers:
                concrete_address = state.current_state.base_addr
                state.add_path_constraint(Equals(address, BV(concrete_address, 32)))
                state.current_state.concrete_symbolic_pointers[address.symbol_name()] = concrete_address
                state.current_state.base_addr = state.current_state.base_addr + 1
            else:
                concrete_address = state.current_state.concrete_symbolic_pointers[address.symbol_name()]
            symb_elems ={}
            rec = SubState.records[state.current_state.get_variable_type(self.record)]
            for k, v in zip(rec.elements, rec.types):
                if isinstance(v, str):
                    symb_elems[k] = Symbol(f"{address.symbol_name()}_{k}", BVType(32))
                else:
                    symb_elems[k] = Symbol(f"{address.symbol_name()}_{k}", INT)
            state.current_state.addr_map[concrete_address] = symb_elems
            return state.current_state.addr_map[concrete_address][self.element]

    def type_check(self, context):
        rec_type = context.variables[self.record]
        record = SubState.records[rec_type]
        return record.types[record.elements.index(self.element)], ""


class Value(AtomicExpression):
    def __init__(self, value, type):
        self.value = value
        self.type = type

    def eval(self, state):
        return [[PathConstraint(), self.value]]

    def type_check(self, context):
        return self.type, ""

    def __repr__(self):
        return f"{self.value}"

class UniqueSymbol(Value):
    def __init__(self, type):
        self.type = type

    def type_check(self, context):
        return self.type, ""

    def eval(self, state):
        return [[PathConstraint(), FreshSymbol(self.type)]]

    def __repr__(self):
        return "$sym"

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
        new_vs = []
        for lvs in lhs:
            for rvs in rhs:
                new_vs.append([lvs[0].apply_AND(rvs[0]), self.op(lvs[1], rvs[1])])
        return new_vs

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
        new_vals = []
        for g_a, v_a in arr:
            for g_i, v_i in index:
                new_vals.append([g_a.apply_AND(g_i), Select(v_a.get_array(), v_i)])
        return new_vals

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
        values = []
        for g, v in self.default.eval(state):
            values.append([g, YouVerifyArray(v, self.length)])
        return values

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
        state.advance_pc()

class BeginMergeStatement(Statement):
    def exec(self, state):
        state.in_conditional = True
        state.advance_pc()

class EndMergeStatement(Statement):
    def exec(self, state):
        state.in_conditional = False
        state.advance_pc()

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
            state.current_state.pop_frame(self.expression.eval(state))
        else:
            state.current_state.pop_frame(self.expression)
        state.advance_pc()

class Assume(Statement):
    def __init__(self, expression):
        self.expression = expression

    def type_check(self, context):
        cond_type, err = self.expression.type_check(context)
        if err:
            return cond_type, err
        return None, "" if cond_type == BOOL else "The condition to a conditional branch must be a boolean value."

    def exec(self, state):
        state.add_path_constraint(self.expression.eval(state))
        state.advance_pc()

class Assert(Statement):
    def __init__(self, expression):
        self.expression = expression

    def type_check(self, context):
        cond_type, err = self.expression.type_check(context)
        if err:
            return cond_type, err
        return None, "" if cond_type == BOOL else "The condition to a conditional branch must be a boolean value."


    def exec(self, state):
        #TODO: IMPLEMENT
        state.advance_pc()

class Pointer_Dereference_Expression(Expression):
    def __init__(self, name):
        self.name = name

    def eval(self, state):
        variable = state.get_variable(self.name)
        state.add_path_constraint(And(GE(variable.index, Int(0)), LT(variable.index, variable.length)))
        return Select(variable.get_array(), variable.index)

class Alloc_Concrete(Statement):
    def __init__(self, target, record, arguments):
        self.target = target
        self.record = record
        self.arguments = arguments

    def type_check(self, context):
        target, target_issue = self.target.type_check(context)
        record = SubState.records[self.record]
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
        address = state.current_state.base_addr
        arguments = [arg.eval(state) for arg in self.arguments]
        state.current_state.addr_map[address] = {k: v for k, v in zip(SubState.records[self.record].elements, arguments)}
        state.current_state.base_addr = state.current_state.base_addr + 1
        state.assign_variable(self.target.name, BV(address, 32))
        state.advance_pc()

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
        state.advance_pc()

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
            value = self.expression.eval(state)
            new_arr = [[g, copy(v)] for g, v in arr]
            new_values = []
            for g_a, v_a in new_arr:
                for g_i, v_i in index:
                    for g_v, v_v in value:
                        v_a.set_array(Store(v_a.get_array(), v_i, v_v))
                        new_values.append([g_v.apply_AND(g_i).apply_AND(g_a), v_a])
            state.assign_variable(self.target.arr.name, new_values)
        elif isinstance(self.target, RecordIndexExpression):
            address = simplify(state.get_variable(self.target.record))
            state.addr_map[address.constant_value()][self.target.element] = self.expression.eval(state)
        else:
            state.assign_variable(self.target.name, self.expression.eval(state))
        state.advance_pc()

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
            state.add_path_constraint(And(GE(i, Int(0)), LT(i, a.length)))
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
            state.advance_pc()
        else:
            function = state.current_state.frame_stack[0].function.functions[self.function]

            arguments = []
            for argument in self.arguments:
                arguments.append(argument.eval(state))
            wrapped_target = wrap_target_arr_index(self.target.arr, self.target.index)\
                if isinstance(self.target, ArrayIndexExpression) else wrap_target_var(self.target)
            state.current_state.push_frame(Frame(function, 0, {k: [v.name, None] for k, v in function.variables.items()}, wrapped_target))
            for i, param in enumerate(function.params):
                state.assign_variable(param, copy(arguments[i]))
            state.advance_pc(0)

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

        function = state.current_state.frame_stack[0].function.functions[self.function]

        arguments = []
        for argument in self.arguments:
            arguments.append(argument.eval(state))

        state.current_state.push_frame(Frame(function, 0, {k: [v.name, None] for k, v in function.variables.items()}, None))
        for i, param in enumerate(function.params):
            state.assign_variable(param, arguments[i])
        state.advance_pc(0)

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
        state.conditional_branch(self.condition.eval(state), state.head_frame.function.labels[self.dest])

    def __repr__(self):
        return f"if {self.condition} goto {self.dest}"

class UnconditionalBranch(ConditionalBranch):
    def __init__(self, dest):
        self.dest = dest
    def exec(self, state):
        state.unconditional_branch(state.head_frame.function.labels[self.dest])

    def type_check(self, context):
        return None, ""

    def __repr__(self):
        return f"goto {self.dest}"
