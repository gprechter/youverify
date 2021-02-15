//
// Created by Griffin Prechter on 2/7/21.
//

#include "ConsumeValue.h"

int consumeValueAsInteger(RT_Value value) {
    int integerValue = *((int *)value.content);
    free(value.content);
    return integerValue;
}

bool consumeValueAsBoolean(RT_Value value) {
    bool booleanValue = *((bool *)value.content);
    free(value.content);
    return booleanValue;
}

float consumeValueAsReal(RT_Value value) {
    float realValue = *((float *)value.content);
    free(value.content);
    return realValue;
}

float consumeValueAsFP(RT_Value value) {
    float realValue = *((float *)value.content);
    free(value.content);
    return realValue;
}