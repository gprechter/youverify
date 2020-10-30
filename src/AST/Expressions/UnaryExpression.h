//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_UNARYEXPRESSION_H
#define YOUVERIFY_UNARYEXPRESSION_H

#include "AST/Operator.h"
#include "AtomicExpression.h"

typedef struct unaryexpression {
    OPERATOR_TYPE op;
    ATOMIC_EXPRESSION operand;
} UNARY_EXPRESSION;

#endif //YOUVERIFY_UNARYEXPRESSION_H
