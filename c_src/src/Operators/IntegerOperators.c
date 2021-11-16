//
// Created by Griffin Prechter on 2/7/21.
//

#include "IntegerOperators.h"
#include "ConsumeValue.h"

RT_Value UnaryMinusOperation(RT_Value operand) {
    return newRT_IntegerValue( -consumeValueAsInteger(operand) );
}

RT_Value UnaryAbsOperation(RT_Value operand) {
    int value = consumeValueAsInteger(operand);
    return newRT_IntegerValue( value < 0 ? -value : value);
}

RT_Value BinaryAddOperation(RT_Value left, RT_Value right) {
    int lVal = consumeValueAsInteger(left);
    int rVal = consumeValueAsInteger(right);
    return newRT_IntegerValue( lVal + rVal );
}

RT_Value BinarySubOperation(RT_Value left, RT_Value right) {
    int lVal = consumeValueAsInteger(left);
    int rVal = consumeValueAsInteger(right);
    return newRT_IntegerValue( lVal - rVal );
}

RT_Value BinaryMulOperation(RT_Value left, RT_Value right) {
    int lVal = consumeValueAsInteger(left);
    int rVal = consumeValueAsInteger(right);
    return newRT_IntegerValue( lVal * rVal );
}
RT_Value BinaryDivOperation(RT_Value left, RT_Value right) {
    int lVal = consumeValueAsInteger(left);
    int rVal = consumeValueAsInteger(right);
    return newRT_IntegerValue( lVal / rVal );
}
RT_Value BinaryModOperation(RT_Value left, RT_Value right) {
    int lVal = consumeValueAsInteger(left);
    int rVal = consumeValueAsInteger(right);
    return newRT_IntegerValue( lVal % rVal );
}
RT_Value BinaryLEQOperation(RT_Value left, RT_Value right) {
    int lVal = consumeValueAsInteger(left);
    int rVal = consumeValueAsInteger(right);
    return newRT_BooleanValue( lVal <= rVal );
}
RT_Value BinaryLEOperation(RT_Value left, RT_Value right) {
    int lVal = consumeValueAsInteger(left);
    int rVal = consumeValueAsInteger(right);
    return newRT_BooleanValue( lVal < rVal );
}
RT_Value BinaryGEQOperation(RT_Value left, RT_Value right) {
    int lVal = consumeValueAsInteger(left);
    int rVal = consumeValueAsInteger(right);
    return newRT_BooleanValue( lVal >= rVal );
}
RT_Value BinaryGEOperation(RT_Value left, RT_Value right) {
    int lVal = consumeValueAsInteger(left);
    int rVal = consumeValueAsInteger(right);
    return newRT_BooleanValue( lVal > rVal );
}