//
// Created by Griffin Prechter on 2/8/21.
//

#ifndef YOUVERIFY_BITVECTOROPERATORS_H
#define YOUVERIFY_BITVECTOROPERATORS_H

#include "Runtime/RT_Value.h"

RT_Value UnaryBV2NatOperation(RT_Value operand);
RT_Value UnaryNat2BVOperation(RT_Value operand);

RT_Value UnaryBVNotOperation(RT_Value operand);
RT_Value UnaryBVNegOperation(RT_Value operand);

unsigned long BV2Nat(RT_Value operand);
RT_Value Nat2BV(unsigned long operand, int numBits);

RT_Value BinaryBVConcatOperation(RT_Value left, RT_Value right);

RT_Value BinaryBVAndOperation(RT_Value left, RT_Value right);
RT_Value BinaryBVOrOperation(RT_Value left, RT_Value right);
RT_Value BinaryBVAddOperation(RT_Value left, RT_Value right);
RT_Value BinaryBVMulOperation(RT_Value left, RT_Value right);
RT_Value BinaryBVDivOperation(RT_Value left, RT_Value right);
RT_Value BinaryBVRemOperation(RT_Value left, RT_Value right);

RT_Value BinaryBVShlOperation(RT_Value left, RT_Value right);
RT_Value BinaryBVLshrOperation(RT_Value left, RT_Value right);
RT_Value BinaryBVUltOperation(RT_Value left, RT_Value right);

RT_Value TernaryBVExtractOperation(RT_Value first, RT_Value second, RT_Value third);

#endif //YOUVERIFY_BITVECTOROPERATORS_H
