//
// Created by Griffin Prechter on 2/8/21.
//

#ifndef YOUVERIFY_REALOPERATORS_H
#define YOUVERIFY_REALOPERATORS_H

#include "Runtime/RT_Value.h"

RT_Value UnaryRMinusOperation(RT_Value operand);

RT_Value BinaryRAddOperation(RT_Value left, RT_Value right);
RT_Value BinaryRSubOperation(RT_Value left, RT_Value right);
RT_Value BinaryRMulOperation(RT_Value left, RT_Value right);
RT_Value BinaryRDivOperation(RT_Value left, RT_Value right);
RT_Value BinaryRLEQOperation(RT_Value left, RT_Value right);
RT_Value BinaryRLEOperation(RT_Value left, RT_Value right);
RT_Value BinaryRGEQOperation(RT_Value left, RT_Value right);
RT_Value BinaryRGEOperation(RT_Value left, RT_Value right);

#endif //YOUVERIFY_REALOPERATORS_H
