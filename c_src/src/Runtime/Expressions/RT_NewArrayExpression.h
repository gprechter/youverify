//
// Created by Griffin Prechter on 1/8/21.
//

#ifndef YOUVERIFY_RT_NEWARRAYEXPRESSION_H
#define YOUVERIFY_RT_NEWARRAYEXPRESSION_H

#include "AST/Value.h"
#include "Runtime/Expressions/RT_AtomicExpression.h"

typedef struct _RT_NewArrayExpression {
    TYPE type;
    int numElems;
    RT_AtomicExpression* elements;
} RT_NewArrayExpression;

#endif //YOUVERIFY_RT_NEWARRAYEXPRESSION_H
