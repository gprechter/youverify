//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_UNARYEXPRESSION_H
#define YOUVERIFY_UNARYEXPRESSION_H

#include "AtomicExpression.h"
#include "Operators/Operator.h"

typedef struct unaryexpression {
    UnaryOperatorType op;
    ATOMIC_EXPRESSION operand;
} UNARY_EXPRESSION;

#endif //YOUVERIFY_UNARYEXPRESSION_H
