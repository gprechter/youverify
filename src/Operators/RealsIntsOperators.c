//
// Created by Griffin Prechter on 2/8/21.
//

#include <math.h>
#include "RealsIntsOperators.h"
#include "ConsumeValue.h"

RT_Value UnaryToRealOperation(RT_Value operand) {
    int i = consumeValueAsInteger(operand);
    return newRT_RealValue((float) i);
}
RT_Value UnaryToIntOperation(RT_Value operand) {
    float f = consumeValueAsReal(operand);
    return newRT_IntegerValue((int) f);
}
RT_Value UnaryIsIntOperation(RT_Value operand) {
    float f = consumeValueAsReal(operand);
    return newRT_BooleanValue(ceilf(f) == f);
}