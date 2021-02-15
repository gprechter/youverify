//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_RT_ATOMICEXPRESSION_H
#define YOUVERIFY_RT_ATOMICEXPRESSION_H

#include "AST/Expressions/AtomicExpression.h"
#include "Runtime/RT_Variable.h"
#include "Runtime/RT_Value.h"

typedef struct _RT_AtomicExpression {
    ATOMIC_EXPRESSION_TYPE type;
    TYPE valueType;
    union RT_ATOMIC_EXPRESSION_CONTENTS {
        RT_Variable variable;
        RT_Value value;
    } contents;
} RT_AtomicExpression;

#endif //YOUVERIFY_RT_ATOMICEXPRESSION_H
