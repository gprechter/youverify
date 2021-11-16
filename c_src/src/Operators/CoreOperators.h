//
// Created by Griffin Prechter on 2/7/21.
//

#ifndef YOUVERIFY_COREOPERATORS_H
#define YOUVERIFY_COREOPERATORS_H

#include "Runtime/RT_Value.h"

RT_Value UnaryNotOperation(RT_Value operand);

RT_Value BinaryImpliesOperation(RT_Value left, RT_Value right);
RT_Value BinaryAndOperation(RT_Value left, RT_Value right);
RT_Value BinaryOrOperation(RT_Value left, RT_Value right);
RT_Value BinaryXorOperation(RT_Value left, RT_Value right);
RT_Value BinaryEqualsOperation(RT_Value left, RT_Value right);
RT_Value BinaryDistinctOperation(RT_Value left, RT_Value right);

RT_Value TernaryITEOperation(RT_Value first, RT_Value second, RT_Value third);

#endif //YOUVERIFY_COREOPERATORS_H
