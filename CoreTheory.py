from pysmt.typing import BOOL
from pysmt.shortcuts import Not, Implies, And, Or, Xor, Equals, NotEquals, Ite, TRUE, FALSE
from OperatorWrapper import binary_operator_wrapper

CORE_YVR_TO_PYSMT_SORT = {
    "BOOL": BOOL
}

CORE_YVR_TO_PYSMT_UNARY_OP = {
    "!": Not
}

CORE_YVR_TO_PYSMT_BINARY_OP = {
    "=>": binary_operator_wrapper(Implies),
    "&": binary_operator_wrapper(And),
    "|": binary_operator_wrapper(Or),
    "^": binary_operator_wrapper(Xor),
    "==": binary_operator_wrapper(Equals),
    "!=": binary_operator_wrapper(NotEquals)
}

CORE_YVR_TO_PYSMT_TERNARY_OP = {
    "?": Ite
}

YVR_BOOL_TO_PYSMT = {
    "true": TRUE(),
    "false": FALSE()
}
