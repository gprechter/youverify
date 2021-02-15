//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_RT_UNARYEXPRESSION_H
#define YOUVERIFY_RT_UNARYEXPRESSION_H

#include "Operators/Operator.h"
#include "AST/Expressions/UnaryExpression.h"
#include "RT_AtomicExpression.h"

typedef struct _RT_UnaryExpression {
    UnaryOperation op;
    RT_AtomicExpression operand;
} RT_UnaryExpression;

#endif //YOUVERIFY_UNARYEXPRESSION_H
