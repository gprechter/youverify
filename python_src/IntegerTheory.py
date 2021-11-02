from pysmt.typing import INT
from pysmt.shortcuts import Minus, Plus, Times, Div, LE, LT, GE, GT, Int, BVSDiv, SBV, simplify, Ite

def unsupported(f=None, s=None, t=None):
    assert False, "Unsupported Operator"

INTEGER_YVR_TO_PYSMT_SORT = {
    "INT": INT
}

INTEGER_YVR_TO_PYSMT_UNARY_OP = {
    "-": (lambda operand: Minus(Int(0), operand)),
    "@": (lambda operand: Ite(LT(operand, Int(0)), Minus(Int(0), operand), operand))
}

def concrete_div(lhs, rhs):
    lhs, rhs = simplify(lhs), simplify(rhs)
    assert lhs.is_constant() and rhs.is_constant() and rhs is not 0
    return Int(int(lhs.constant_value() / rhs.constant_value()))

def concrete_rem(lhs, rhs):
    lhs, rhs = simplify(lhs), simplify(rhs)
    assert lhs.is_constant() and rhs.is_constant() and rhs is not 0
    return Int(lhs.constant_value() % rhs.constant_value())

INTEGER_YVR_TO_PYSMT_BINARY_OP = {
    "-": Minus,
    "+": Plus,
    "*": Times,
    "/": concrete_div,
    "%": concrete_rem,
    "<=": LE,
    "<": LT,
    ">=": GE,
    ">": GT
}