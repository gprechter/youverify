//
// Created by Griffin Prechter on 1/8/21.
//

#ifndef YOUVERIFY_ARRAYACCESSEXPRESSION_H
#define YOUVERIFY_ARRAYACCESSEXPRESSION_H

#include "AST/Expressions/AtomicExpression.h"

typedef struct arrayaccessexpression {
     Identifier arr;
     ATOMIC_EXPRESSION index;
} ARRAY_ACCESS_EXPRESSION;

#endif //YOUVERIFY_ARRAYACCESSEXPRESSION_H
