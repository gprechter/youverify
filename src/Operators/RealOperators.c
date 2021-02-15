//
// Created by Griffin Prechter on 2/8/21.
//

#include "RealOperators.h"
#include "ConsumeValue.h"

RT_Value UnaryRMinusOperation(RT_Value operand) {
    return newRT_RealValue( -consumeValueAsReal(operand) );
}

RT_Value BinaryRAddOperation(RT_Value left, RT_Value right) {
    float lVal = consumeValueAsReal(left);
    float rVal = consumeValueAsReal(right);
    return newRT_RealValue( lVal + rVal );
}

RT_Value BinaryRSubOperation(RT_Value left, RT_Value right) {
    float lVal = consumeValueAsReal(left);
    float rVal = consumeValueAsReal(right);
    return newRT_RealValue( lVal - rVal );
}

RT_Value BinaryRMulOperation(RT_Value left, RT_Value right) {
    float lVal = consumeValueAsReal(left);
    float rVal = consumeValueAsReal(right);
    return newRT_RealValue( lVal * rVal );
}
RT_Value BinaryRDivOperation(RT_Value left, RT_Value right) {
    float lVal = consumeValueAsReal(left);
    float rVal = consumeValueAsReal(right);
    return newRT_RealValue( lVal / rVal );
}
RT_Value BinaryRLEQOperation(RT_Value left, RT_Value right) {
    float lVal = consumeValueAsReal(left);
    float rVal = consumeValueAsReal(right);
    return newRT_BooleanValue( lVal <= rVal );
}
RT_Value BinaryRLEOperation(RT_Value left, RT_Value right) {
    float lVal = consumeValueAsReal(left);
    float rVal = consumeValueAsReal(right);
    return newRT_BooleanValue( lVal < rVal );
}
RT_Value BinaryRGEQOperation(RT_Value left, RT_Value right) {
    float lVal = consumeValueAsReal(left);
    float rVal = consumeValueAsReal(right);
    return newRT_BooleanValue( lVal >= rVal );
}
RT_Value BinaryRGEOperation(RT_Value left, RT_Value right) {
    float lVal = consumeValueAsReal(left);
    float rVal = consumeValueAsReal(right);
    return newRT_BooleanValue( lVal > rVal );
}