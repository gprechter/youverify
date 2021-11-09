from pysmt.typing import INT, BOOL, BVType, ArrayType, _BVType

def both_same(l, r):
    if isinstance(l, _BVType):
        return both_BVType(l, r)
    return l == r

def both_INT(l, r):
    return l == INT and r == INT

def both_BOOL(l, r):
    return l == BOOL and r == BOOL

def both_BVType(l, r):
    return isinstance(l, _BVType) and isinstance(r, _BVType) and l.width == r.width

def both_records_or_null(l, r):
    return (isinstance(l, str) and (isinstance(r,str) or isinstance(r, _BVType))) or (isinstance(r, str) and (isinstance(l,str) or isinstance(l, _BVType)))


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

builtin_type_checking_rules = {"bvnot": (lambda o: isinstance(o, _BVType), lambda o: o, 1),
                           "bvand": (both_BVType, lambda l, r: l, 2),
                           "bvor": (both_BVType, lambda l, r: l, 2),
                           "bvneg": (lambda o: isinstance(o, _BVType), lambda o: o, 1),
                           "bvadd": (both_BVType, lambda l, r: l, 2),
                           "bvmul": (both_BVType, lambda l, r: l, 2),
                           "bvdiv": (both_BVType, lambda l, r: l, 2),
                           "bvrem": (both_BVType, lambda l, r: l, 2),
                           "bvshl": (both_BVType, lambda l, r: l, 2),
                           "bvlshr": (both_BVType, lambda l, r: l, 2),
                           "bvult": (both_BVType, lambda l, r: BOOL, 2),
                           "concat": (lambda a, b: isinstance(a, _BVType) and isinstance(b, _BVType),
                                      lambda a, b: BVType(a.width + b.width), 2),
                           "bv2nat": (lambda o: isinstance(o, _BVType), lambda o: INT, 1),
                           "extract": (lambda bv, s, e: (isinstance(bv, _BVType) and s == INT and e == INT), lambda bv, s, e: None, 3)
}