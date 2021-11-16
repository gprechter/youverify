//
// Created by Griffin Prechter on 1/8/21.
//

#ifndef YOUVERIFY_RT_ARRAYACCESSEXPRESSION_H
#define YOUVERIFY_RT_ARRAYACCESSEXPRESSION_H

#include "Runtime/Expressions/RT_AtomicExpression.h"
#include "AST/Value.h"

typedef struct _RT_ArrayAccessExpression {
    TYPE elemType;
    RT_Variable arr;
    RT_AtomicExpression index;
} RT_ArrayAccessExpression;

#endif //YOUVERIFY_RT_ARRAYACCESSEXPRESSION_H
