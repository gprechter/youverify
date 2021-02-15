//
// Created by Griffin Prechter on 1/2/21.
//

#ifndef YOUVERIFY_RT_TERNARYEXPRESSION_H
#define YOUVERIFY_RT_TERNARYEXPRESSION_H

#include "Operators/Operator.h"
#include "RT_AtomicExpression.h"

typedef struct _RT_TernaryExpression {
    TernaryOperation op;
    RT_AtomicExpression first;
    RT_AtomicExpression second;
    RT_AtomicExpression third;
} RT_TernaryExpression;

#endif //YOUVERIFY_RT_TERNARYEXPRESSION_H
