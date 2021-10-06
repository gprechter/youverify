from pysmt.typing import BOOL, INT, ArrayType, BVType
from pysmt.shortcuts import And, Or, Plus, Minus, GE, LT
from pysmt.shortcuts import TRUE, FALSE, BVAdd, BVConcat, BVExtract
from pysmt.shortcuts import BVNot, BVAnd, BVOr
from pysmt.shortcuts import BVNeg, BVAdd, BVMul, BVUDiv, BVURem
from pysmt.shortcuts import BVLShl, BVLShr, BVULT
from CoreTheory import *
from IntegerTheory import *

YVR_SORT_TO_PYSMT = {
    "ARRAY": ArrayType,
    "BV": BVType
}
YVR_SORT_TO_PYSMT.update(CORE_YVR_TO_PYSMT_SORT)
YVR_SORT_TO_PYSMT.update(INTEGER_YVR_TO_PYSMT_SORT)

YVR_UNARY_OP_TO_PYSMT = {}
YVR_UNARY_OP_TO_PYSMT.update(CORE_YVR_TO_PYSMT_UNARY_OP)
YVR_UNARY_OP_TO_PYSMT.update(INTEGER_YVR_TO_PYSMT_UNARY_OP)

YVR_BINARY_OP_TO_PYSMT = {}
YVR_BINARY_OP_TO_PYSMT.update(CORE_YVR_TO_PYSMT_BINARY_OP)
YVR_BINARY_OP_TO_PYSMT.update(INTEGER_YVR_TO_PYSMT_BINARY_OP)

YVR_TERNARY_OP_TO_PYSMT = {}
YVR_TERNARY_OP_TO_PYSMT.update(CORE_YVR_TO_PYSMT_TERNARY_OP)

YVR_BUILTIN_OP_TO_PYSMT = {"bvnot": BVNot,
                           "bvand": BVAnd,
                           "bvor": BVOr,
                           "bvneg": BVNeg,
                           "bvadd": BVAdd,
                           "bvmul": BVMul,
                           "bvudiv": BVUDiv,
                           "bvurem": BVURem,
                           "bvshl": BVLShl,
                           "bvlshr": BVLShr,
                           "bvult": BVULT,
                           "concat": BVConcat,
                           "extract": lambda bv, s, e: BVExtract(bv, s.constant_value(), e.constant_value())}