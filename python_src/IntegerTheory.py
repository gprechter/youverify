from pysmt.typing import INT
from pysmt.shortcuts import Minus, Plus, Times, Div, LE, LT, GE, GT, Int

def unsupported(f=None, s=None, t=None):
    assert False, "Unsupported Operator"

INTEGER_YVR_TO_PYSMT_SORT = {
    "INT": INT
}

INTEGER_YVR_TO_PYSMT_UNARY_OP = {
    "-": (lambda operand: Minus(Int(0), operand)),
    "@": unsupported
}

INTEGER_YVR_TO_PYSMT_BINARY_OP = {
    "-": Minus,
    "+": Plus,
    "*": Times,
    "/": Div,
    "%": unsupported,
    "<=": LE,
    "<": LT,
    ">=": GE,
    ">": GT
}