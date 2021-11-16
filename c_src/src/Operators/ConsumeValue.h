//
// Created by Griffin Prechter on 2/7/21.
//

#ifndef YOUVERIFY_CONSUMEVALUE_H
#define YOUVERIFY_CONSUMEVALUE_H

#include "stdbool.h"
#include "Runtime/RT_Value.h"

int consumeValueAsInteger(RT_Value value);
bool consumeValueAsBoolean(RT_Value value);
float consumeValueAsReal(RT_Value value);
float consumeValueAsFP(RT_Value value);
#endif //YOUVERIFY_CONSUMEVALUE_H
