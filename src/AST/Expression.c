//
// Created by Griffin Prechter on 10/29/20.
//

#include "Expression.h"

EXPRESSION newATOMIC_EXPRESSION(ATOMIC_EXPRESSION atomicExpression) {
    EXPRESSION e;
    e.type = E_atomic;
    e.contents.atomicExpression = atomicExpression;
    return e;
}

EXPRESSION newBINARY_EXPRESSION(ATOMIC_EXPRESSION lhs, OPERATOR_TYPE op, ATOMIC_EXPRESSION rhs) {
    EXPRESSION e;
    e.type = E_binary;
    BINARY_EXPRESSION b;
    b.lhs = lhs;
    b.op = op;
    b.rhs = rhs;
    e.contents.binaryExpression = b;
    return e;
}

EXPRESSION newUNARY_EXPRESSION(OPERATOR_TYPE op, ATOMIC_EXPRESSION operand) {
    EXPRESSION e;
    e.type = E_unary;
    UNARY_EXPRESSION u;
    u.op = op;
    u.operand = operand;
    e.contents.unaryExpression = u;
    return e;
}

EXPRESSION newTERNARY_EXPRESSION(ATOMIC_EXPRESSION first, ATOMIC_EXPRESSION second, ATOMIC_EXPRESSION third) {
    EXPRESSION e;
    e.type = E_ternary;
    TERNARY_EXPRESSION t;
    t.first = first;
    t.second = second;
    t.third = third;
    e.contents.ternaryExpression = t;
    return e;
}