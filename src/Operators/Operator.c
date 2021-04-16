//
// Created by Griffin Prechter on 1/12/21.
//

#include "Operator.h"
#include "CoreOperators.h"
#include "IntegerOperators.h"
#include "RealOperators.h"
#include "BitVectorOperators.h"
#include "RealsIntsOperators.h"
#include "FloatingPointOperators.h"

UnaryOperation UnaryOperators[21];
BinaryOperation BinaryOperators[44];
TernaryOperation TernaryOperators[6];

void initializeOperators() {
    UnaryOperators[U_OP_NOT] = UnaryNotOperation;

    UnaryOperators[U_OP_MINUS] = UnaryMinusOperation;
    UnaryOperators[U_OP_ABS] = UnaryAbsOperation;

    UnaryOperators[U_BV2NAT] = UnaryBV2NatOperation;
    UnaryOperators[U_NAT2BV] = UnaryNat2BVOperation;

    UnaryOperators[U_BVNOT] = UnaryBVNotOperation;
    UnaryOperators[U_BVNEG] = UnaryBVNegOperation;

    UnaryOperators[U_OP_RMINUS] = UnaryRMinusOperation;

    UnaryOperators[U_OP_ITR] = UnaryToRealOperation;
    UnaryOperators[U_OP_RTI] = UnaryToIntOperation;
    UnaryOperators[U_OP_ISINT] = UnaryIsIntOperation;

    UnaryOperators[U_OP_FPABS] = UnaryFPAbsOperation;
    UnaryOperators[U_OP_FPNEG] = UnaryFPNegOperation;
    UnaryOperators[U_OP_FPISNORMAL] = UnaryFPIsNormalOperation;
    UnaryOperators[U_OP_FPISSUBNORMAL] = UnaryFPIsSubnormalOperation;
    UnaryOperators[U_OP_FPISZERO] = UnaryFPIsZeroOperation;
    UnaryOperators[U_OP_FPISINFINITE] = UnaryFPIsInfiniteOperation;
    UnaryOperators[U_OP_FPISNAN] = UnaryFPIsNaNOperation;
    UnaryOperators[U_OP_FPISNEGATIVE] = UnaryFPIsNegativeOperation;
    UnaryOperators[U_OP_FPISPOSITIVE] = UnaryFPIsPositiveOperation;
    UnaryOperators[U_OP_TOFP] = UnaryToFPOperation;


    BinaryOperators[B_OP_ADD] = BinaryAddOperation;
    BinaryOperators[B_OP_AND] = BinaryAndOperation;
    BinaryOperators[B_OP_DISTINCT] = BinaryDistinctOperation;
    BinaryOperators[B_OP_EQUALS] = BinaryEqualsOperation;
    BinaryOperators[B_OP_IMPLIES] = BinaryImpliesOperation;
    BinaryOperators[B_OP_OR] = BinaryOrOperation;
    BinaryOperators[B_OP_SUB] = BinarySubOperation;
    BinaryOperators[B_OP_XOR] = BinaryXorOperation;
    BinaryOperators[B_OP_MUL] = BinaryMulOperation;
    BinaryOperators[B_OP_DIV] = BinaryDivOperation;
    BinaryOperators[B_OP_MOD] = BinaryModOperation;
    BinaryOperators[B_OP_LEQ] = BinaryLEQOperation;
    BinaryOperators[B_OP_LE] = BinaryLEOperation;
    BinaryOperators[B_OP_GEQ] = BinaryGEQOperation;
    BinaryOperators[B_OP_GE] = BinaryGEOperation;

    BinaryOperators[B_BVCONCAT] = BinaryBVConcatOperation;
    BinaryOperators[B_BVAND] = BinaryBVAndOperation;
    BinaryOperators[B_BVOR] = BinaryBVOrOperation;
    BinaryOperators[B_BVADD] = BinaryBVAddOperation;
    BinaryOperators[B_BVMUL] = BinaryBVMulOperation;
    BinaryOperators[B_BVUDIV] = BinaryBVDivOperation;
    BinaryOperators[B_BVUREM] = BinaryBVRemOperation;
    BinaryOperators[B_BVSHL] = BinaryBVShlOperation;
    BinaryOperators[B_BVLSHR] = BinaryBVLshrOperation;
    BinaryOperators[B_BVULT] = BinaryBVUltOperation;

    BinaryOperators[B_OP_RADD] = BinaryRAddOperation;
    BinaryOperators[B_OP_RSUB] = BinaryRSubOperation;
    BinaryOperators[B_OP_RMUL] = BinaryRMulOperation;
    BinaryOperators[B_OP_RDIV] = BinaryRDivOperation;
    BinaryOperators[B_OP_RLEQ] = BinaryRLEQOperation;
    BinaryOperators[B_OP_RLE] = BinaryRLEOperation;
    BinaryOperators[B_OP_RGEQ] = BinaryRGEQOperation;
    BinaryOperators[B_OP_RGE] = BinaryRGEOperation;

    BinaryOperators[B_OP_FPSQRT] = BinaryFPSqrtOperation;
    BinaryOperators[B_OP_FPREM] = BinaryFPRemOperation;
    BinaryOperators[B_OP_FPRound] = BinaryFPRoundToIntegralOperation;
    BinaryOperators[B_OP_FPMIN] = BinaryFPMinOperation;
    BinaryOperators[B_OP_FPMAX] = BinaryFPMaxOperation;
    BinaryOperators[B_OP_FPLEQ] = BinaryFPLeqOperation;
    BinaryOperators[B_OP_FPLT] = BinaryFPLtOperation;
    BinaryOperators[B_OP_FPGEQ] = BinaryFPGeqOperation;
    BinaryOperators[B_OP_FPGT] = BinaryFPGtOperation;
    BinaryOperators[B_OP_FPEQ] = BinaryFPEqOperation;
    BinaryOperators[B_OP_TOFP] = BinaryToFPOperation;

    TernaryOperators[T_ITE] = TernaryITEOperation;

    TernaryOperators[T_BVEXTRACT] = TernaryBVExtractOperation;

    TernaryOperators[T_FPADD] = TernaryFPAddOperation;
    TernaryOperators[T_FPSUB] = TernaryFPSubOperation;
    TernaryOperators[T_FPMUL] = TernaryFPMulOperation;
    TernaryOperators[T_FPDIV] = TernaryFPDivOperation;

}