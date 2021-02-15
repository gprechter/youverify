//
// Created by Griffin Prechter on 2/8/21.
//

#ifndef YOUVERIFY_FLOATINGPOINTOPERATORS_H
#define YOUVERIFY_FLOATINGPOINTOPERATORS_H

#include "Runtime/RT_Value.h"

RT_Value UnaryFPAbsOperation(RT_Value operand);
RT_Value UnaryFPNegOperation(RT_Value operand);
RT_Value UnaryFPIsNormalOperation(RT_Value operand);
RT_Value UnaryFPIsSubnormalOperation(RT_Value operand);
RT_Value UnaryFPIsZeroOperation(RT_Value operand);
RT_Value UnaryFPIsInfiniteOperation(RT_Value operand);
RT_Value UnaryFPIsNaNOperation(RT_Value operand);
RT_Value UnaryFPIsNegativeOperation(RT_Value operand);
RT_Value UnaryFPIsPositiveOperation(RT_Value operand);
RT_Value UnaryToFPOperation(RT_Value operand);

RT_Value TernaryFPAddOperation(RT_Value first, RT_Value second, RT_Value third);
RT_Value TernaryFPSubOperation(RT_Value first, RT_Value second, RT_Value third);
RT_Value TernaryFPMulOperation(RT_Value first, RT_Value second, RT_Value third);
RT_Value TernaryFPDivOperation(RT_Value first, RT_Value second, RT_Value third);

//RT_Value TernaryFPFmaOperation(RT_Value first, RT_Value second, RT_Value third);

RT_Value BinaryFPSqrtOperation(RT_Value left, RT_Value right);
RT_Value BinaryFPRemOperation(RT_Value left, RT_Value right);
RT_Value BinaryFPRoundToIntegralOperation(RT_Value left, RT_Value right);
RT_Value BinaryFPMinOperation(RT_Value left, RT_Value right);
RT_Value BinaryFPMaxOperation(RT_Value left, RT_Value right);
RT_Value BinaryFPLeqOperation(RT_Value left, RT_Value right);
RT_Value BinaryFPLtOperation(RT_Value left, RT_Value right);
RT_Value BinaryFPGeqOperation(RT_Value left, RT_Value right);
RT_Value BinaryFPGtOperation(RT_Value left, RT_Value right);
RT_Value BinaryFPEqOperation(RT_Value left, RT_Value right);
RT_Value BinaryToFPOperation(RT_Value left, RT_Value right);
#endif //YOUVERIFY_FLOATINGPOINTOPERATORS_H
