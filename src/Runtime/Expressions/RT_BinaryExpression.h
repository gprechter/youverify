//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_RT_BINARYEXPRESSION_H
#define YOUVERIFY_RT_BINARYEXPRESSION_H

#include "Operators/Operator.h"
#include "RT_AtomicExpression.h"

typedef struct _RT_BinaryExpression {
    RT_AtomicExpression lhs;
    BinaryOperation op;
    RT_AtomicExpression rhs;
} RT_BinaryExpression;

#endif //YOUVERIFY_BINARYEXPRESSION_H
