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

class BinaryExpression(Expression):
    def __init__(self, lhs, op, rhs):
        self.lhs = lhs
        self.op = op
        self.rhs = rhs

    def eval(self, state):
        return self.op(self.lhs.eval(state), self.rhs.eval(state))

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

class Statement:
    def exec(self, state):
        return state.advance_pc()

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

program = Program()
program.append(Assignment(Variable("a"), Value(TRUE())))
program.append(Assignment(Variable("b"), Value(FALSE())))
#program.append(ConditionalBranch(Value(Symbol("c")), "branch"))
program.append(Assignment(Variable("a"), BinaryExpression(Variable("a"), And, Variable("b"))))
#program.append(UnconditionalBranch("else"))
#program.append(Assignment(Variable("a"), BinaryExpression(Variable("a"), Or, Variable("b"))), label="branch")
#program.append(Statement(), label="else")

'''
program = Program()
program.append(Assignment(Variable("privateData"), Value(Array(INT, Symbol("NULL", INT)))))
program.append(Assignment(Variable("k"), Value(Int(3))))
program.append(Assignment(Variable("i"), Value(Int(0))))
program.append(ConditionalBranch(BinaryExpression(Variable("k"), LE, Variable("i")), "END1"), label="LOOP1")
program.append(Assignment(ArrayIndexExpression(Variable("privateData"), Variable("i")), UniqueSymbol(INT)))
program.append(Assignment(Variable("i"), BinaryExpression(Variable("i"), Plus, Value(Int(1)))))
program.append(UnconditionalBranch("LOOP1"))
program.append(Assignment(Variable("i"), Value(Int(0))), label="END1")
program.append(Assignment(Variable("buf"), Value(Array(INT, Symbol("NULL", INT)))))
program.append(Assignment(Variable("buf_length"), Value(Int(0))))

program.append(ConditionalBranch(BinaryExpression(Variable("k"), LE, Variable("i")), "END2"), label="LOOP2")
program.append(Assignment(Variable("t"), ArrayIndexExpression(Variable("privateData"), Variable("i"))))
program.append(ConditionalBranch(BinaryExpression(Variable("t"), LT, Value(Int(0))), "ELSE"), label="COND")
program.append(Assignment(ArrayIndexExpression(Variable("buf"), Variable("buf_length")), Value(Int(1))))
program.append(Assignment(Variable("buf_length"), BinaryExpression(Variable("buf_length"), Plus, Value(Int(1)))))
program.append(UnconditionalBranch("ENDCOND"))
program.append(Assignment(ArrayIndexExpression(Variable("buf"), Variable("buf_length")), Value(Int(0))), label="ELSE")
program.append(Assignment(Variable("buf_length"), BinaryExpression(Variable("buf_length"), Plus, Value(Int(1)))))
program.append(Assignment(Variable("i"), BinaryExpression(Variable("i"), Plus, Value(Int(1)))), label="ENDCOND")
program.append(UnconditionalBranch("LOOP2"))
program.append(Statement(), label="END2")
'''
