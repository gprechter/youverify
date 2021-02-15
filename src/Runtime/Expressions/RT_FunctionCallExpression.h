//
// Created by Griffin Prechter on 11/24/20.
//

#ifndef YOUVERIFY_RT_FUNCTIONCALLEXPRESSION_H
#define YOUVERIFY_RT_FUNCTIONCALLEXPRESSION_H

#include "RT_AtomicExpression.h"
#include "Queue.h"

typedef struct _RT_FunctionCallExpression {
    int index;
    TYPE returnType;
    int numArgs;
    RT_AtomicExpression* arguments;
} RT_FunctionCallExpression;

#endif //YOUVERIFY_FUNCTIONCALLEXPRESSION_H
