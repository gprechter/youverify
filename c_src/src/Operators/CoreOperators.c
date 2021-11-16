//
// Created by Griffin Prechter on 2/7/21.
//

#include "CoreOperators.h"
#include "ConsumeValue.h"

RT_Value UnaryNotOperation(RT_Value operand) {
    return newRT_BooleanValue( !consumeValueAsBoolean(operand) );
}

RT_Value BinaryImpliesOperation(RT_Value left, RT_Value right) {
    bool lVal = consumeValueAsBoolean(left);
    bool rVal = consumeValueAsBoolean(right);
    return newRT_BooleanValue( !lVal || (lVal && rVal) );
}

RT_Value BinaryAndOperation(RT_Value left, RT_Value right) {
    bool lVal = consumeValueAsBoolean(left);
    bool rVal = consumeValueAsBoolean(right);
    return newRT_BooleanValue( lVal && rVal );
}

RT_Value BinaryOrOperation(RT_Value left, RT_Value right) {
    bool lVal = consumeValueAsBoolean(left);
    bool rVal = consumeValueAsBoolean(right);
    return newRT_BooleanValue( lVal || rVal );
}

RT_Value BinaryXorOperation(RT_Value left, RT_Value right) {
    bool lVal = consumeValueAsBoolean(left);
    bool rVal = consumeValueAsBoolean(right);
    return newRT_BooleanValue( lVal != rVal );
}

RT_Value BinaryEqualsOperation(RT_Value left, RT_Value right) {
    RT_Value res;
    if (left.type.id == TID_boolean && right.type.id == TID_boolean) {
        bool lVal = consumeValueAsBoolean(left);
        bool rVal = consumeValueAsBoolean(right);
        res = newRT_BooleanValue(lVal == rVal);
    } else if (left.type.id == TID_integer && right.type.id == TID_integer) {
        int lVal = consumeValueAsInteger(left);
        int rVal = consumeValueAsInteger(right);
        res = newRT_BooleanValue(lVal == rVal);
    }
    return res;
}

RT_Value BinaryDistinctOperation(RT_Value left, RT_Value right) {
    return newRT_BooleanValue( !consumeValueAsBoolean(BinaryEqualsOperation(left, right)) );
}

RT_Value TernaryITEOperation(RT_Value first, RT_Value second, RT_Value third) {
    RT_Value result;
    if (consumeValueAsBoolean(first)) {
        result = second;
        free(third.content);
    } else {
        result = third;
        free(second.content);
    }
    return result;
}

