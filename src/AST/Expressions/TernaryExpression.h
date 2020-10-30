//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_TERNARYEXPRESSION_H
#define YOUVERIFY_TERNARYEXPRESSION_H

#include "AtomicExpression.h"

typedef struct ternaryexpression {
    ATOMIC_EXPRESSION first;
    ATOMIC_EXPRESSION second;
    ATOMIC_EXPRESSION third;
} TERNARY_EXPRESSION;

#endif //YOUVERIFY_TERNARYEXPRESSION_H
