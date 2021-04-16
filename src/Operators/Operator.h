//
// Created by Griffin Prechter on 1/12/21.
//

#ifndef YOUVERIFY_OPERATOR_H
#define YOUVERIFY_OPERATOR_H

#include "Runtime/RT_Value.h"

typedef RT_Value (*UnaryOperation)(RT_Value operand);
typedef RT_Value (*BinaryOperation)(RT_Value left, RT_Value right);
typedef RT_Value (*TernaryOperation)(RT_Value first, RT_Value second, RT_Value third);

typedef enum _UnaryOperatorType {
    U_OP_NOT,

    U_OP_MINUS, U_OP_ABS,

    U_BV2NAT, U_NAT2BV, U_BVNOT, U_BVNEG,

    U_OP_RMINUS,

    U_OP_RTI, U_OP_ITR, U_OP_ISINT,

    U_OP_FPABS, U_OP_FPNEG, U_OP_FPISNORMAL, U_OP_FPISSUBNORMAL, U_OP_FPISZERO, U_OP_FPISINFINITE, U_OP_FPISNAN, U_OP_FPISNEGATIVE, U_OP_FPISPOSITIVE, U_OP_TOFP
} UnaryOperatorType;
extern UnaryOperation UnaryOperators[21];

typedef enum _BinaryOperatorType {
    B_OP_AND, B_OP_OR, B_OP_IMPLIES, B_OP_XOR, B_OP_DISTINCT, B_OP_EQUALS,

    B_OP_ADD, B_OP_SUB, B_OP_MUL, B_OP_DIV, B_OP_MOD, B_OP_LEQ, B_OP_LE, B_OP_GEQ, B_OP_GE,

    B_BVCONCAT, B_BVAND, B_BVOR, B_BVADD, B_BVMUL, B_BVUDIV, B_BVUREM, B_BVSHL, B_BVLSHR, B_BVULT,

    B_OP_RADD, B_OP_RSUB, B_OP_RMUL, B_OP_RDIV, B_OP_RLEQ, B_OP_RLE, B_OP_RGEQ, B_OP_RGE,

    B_OP_FPSQRT, B_OP_FPREM, B_OP_FPRound, B_OP_FPMIN, B_OP_FPMAX, B_OP_FPLEQ, B_OP_FPLT, B_OP_FPGEQ, B_OP_FPGT, B_OP_FPEQ, B_OP_TOFP
} BinaryOperatorType;
extern BinaryOperation BinaryOperators[44];

typedef enum _TernaryOperatorType {
    T_ITE,
    T_BVEXTRACT,

    T_FPADD, T_FPSUB, T_FPMUL, T_FPDIV

} TernaryOperatorType;
extern TernaryOperation TernaryOperators[6];

void initializeOperators();

int consumeValueAsInteger(RT_Value value);
bool consumeValueAsBoolean(RT_Value value);

#endif //YOUVERIFY_OPERATOR_H
