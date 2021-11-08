from pysmt.typing import INT, BOOL, BVType, ArrayType

def both_same(l, r):
    return l == r

def both_INT(l, r):
    return l == INT and r == INT

def both_BOOL(l, r):
    return l == BOOL and r == BOOL

def both_BVType(l, r):
    return l == BVType and r == BVType and l.width == r.width

def both_records_or_null(l, r):
    return isinstance(l, str) and isinstance(r,str) and (l == 'null' or r == 'null')

unary_type_checking_rules = {
    "-": (lambda o: o == INT, INT),
    "@": (lambda o: o == INT, INT),
    "!": (lambda o: o == BOOL, BOOL)
}

binary_type_checking_rules = {
    "-": (both_INT, INT),
    "+": (both_INT, INT),
    "*": (both_INT, INT),
    "/": (both_INT, INT),
    "%": (both_INT, INT),
    "<=": (both_INT, BOOL),
    "<": (both_INT, BOOL),
    ">=": (both_INT, BOOL),
    ">": (both_INT, BOOL),

    "=>": (both_BOOL, BOOL),
    "&": (both_BOOL, BOOL),
    "|": (both_BOOL, BOOL),
    "^": (both_BOOL, BOOL),

    "==": (lambda l, r: both_same(l,r) or both_records_or_null(l,r), BOOL),
    "!=": (lambda l, r: both_same(l,r) or both_records_or_null(l,r), BOOL)
}