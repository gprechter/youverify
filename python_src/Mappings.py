from pysmt.typing import BOOL, INT, ArrayType
from pysmt.shortcuts import And, Or, Plus, Minus, GE, LT
from pysmt.shortcuts import TRUE, FALSE

YVR_SORT_TO_PYSMT = {
    "BOOL": BOOL,
    "INT": INT,
    "ARRAY": ArrayType
}

YVR_OP_TO_PYSMT = {
    "&": And,
    "|": Or,
    "+": Plus,
    "-": Minus,
    ">=": GE,
    "<": LT
}

YVR_BOOL_TO_PYSMT = {
    "true": TRUE(),
    "false": FALSE()
}