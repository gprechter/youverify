//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_EXPRESSION_H
#define YOUVERIFY_EXPRESSION_H

#include "Expressions/AtomicExpression.h"
#include "Expressions/UnaryExpression.h"
#include "Expressions/BinaryExpression.h"
#include "Expressions/TernaryExpression.h"

typedef enum expressiontype {E_atomic, E_unary, E_binary, E_ternary} EXPRESSION_TYPE;

typedef struct expression {
    EXPRESSION_TYPE type;
    union EXPRESSION_CONTENTS {
        ATOMIC_EXPRESSION atomicExpression;
        UNARY_EXPRESSION unaryExpression;
        BINARY_EXPRESSION binaryExpression;
        TERNARY_EXPRESSION ternaryExpression;
    } contents;
} EXPRESSION;

EXPRESSION newATOMIC_EXPRESSION(ATOMIC_EXPRESSION atomicExpression);

EXPRESSION newUNARY_EXPRESSION(OPERATOR_TYPE op, ATOMIC_EXPRESSION operand);

EXPRESSION newBINARY_EXPRESSION(ATOMIC_EXPRESSION lhs, OPERATOR_TYPE op, ATOMIC_EXPRESSION rhs);

EXPRESSION newTERNARY_EXPRESSION(ATOMIC_EXPRESSION first, ATOMIC_EXPRESSION second, ATOMIC_EXPRESSION third);

#endif //YOUVERIFY_EXPRESSION_H
