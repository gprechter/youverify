//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_BINARYEXPRESSION_H
#define YOUVERIFY_BINARYEXPRESSION_H

#include "Operators/Operator.h"
#include "AtomicExpression.h"

typedef struct binaryexpression {
    ATOMIC_EXPRESSION lhs;
    BinaryOperatorType op;
    ATOMIC_EXPRESSION rhs;
} BINARY_EXPRESSION;

#endif //YOUVERIFY_BINARYEXPRESSION_H
