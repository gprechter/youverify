//
// Created by Griffin Prechter on 2/7/21.
//

#ifndef YOUVERIFY_INTEGEROPERATORS_H
#define YOUVERIFY_INTEGEROPERATORS_H

#include "Runtime/RT_Value.h"

RT_Value UnaryMinusOperation(RT_Value operand);
RT_Value UnaryAbsOperation(RT_Value operand);

RT_Value BinaryAddOperation(RT_Value left, RT_Value right);
RT_Value BinarySubOperation(RT_Value left, RT_Value right);
RT_Value BinaryMulOperation(RT_Value left, RT_Value right);
RT_Value BinaryDivOperation(RT_Value left, RT_Value right);
RT_Value BinaryModOperation(RT_Value left, RT_Value right);
RT_Value BinaryLEQOperation(RT_Value left, RT_Value right);
RT_Value BinaryLEOperation(RT_Value left, RT_Value right);
RT_Value BinaryGEQOperation(RT_Value left, RT_Value right);
RT_Value BinaryGEOperation(RT_Value left, RT_Value right);

#endif //YOUVERIFY_INTEGEROPERATORS_H
