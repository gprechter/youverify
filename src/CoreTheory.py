from pysmt.typing import BOOL
from pysmt.shortcuts import Not, Implies, And, Or, Xor, Equals, NotEquals, Ite, TRUE, FALSE

CORE_YVR_TO_PYSMT_SORT = {
    "BOOL": BOOL
}

CORE_YVR_TO_PYSMT_UNARY_OP = {
    "!": Not
}

CORE_YVR_TO_PYSMT_BINARY_OP = {
    "=>": Implies,
    "&": And,
    "|": Or,
    "^": Xor,
    "==": Equals,
    "!=": NotEquals
}

CORE_YVR_TO_PYSMT_TERNARY_OP = {
    "?": Ite
}

YVR_BOOL_TO_PYSMT = {
    "true": TRUE(),
    "false": FALSE()
}
