//
// Created by Griffin Prechter on 10/30/20.
//
#include <stdio.h>
#include "TCExpression.h"

bool checkEXPRESSION(EXPRESSION expression, VALUE_TYPE *expressionType, SYMBOL_TABLE *table) {
    switch (expression.type) {
        case E_atomic:
            return checkATOMIC_EXPRESSION(expression.contents.atomicExpression, expressionType, table);
        case E_unary:
            return checkUNARY_EXPRESSION(expression.contents.unaryExpression, expressionType, table);
        case E_binary:
            return checkBINARY_EXPRESSION(expression.contents.binaryExpression, expressionType, table);
        case E_ternary:
            return checkTERNARY_EXPRESSION(expression.contents.ternaryExpression, expressionType, table);
        default:
            return false;
    }
}

bool checkBINARY_EXPRESSION(BINARY_EXPRESSION expression, VALUE_TYPE *expressionType, SYMBOL_TABLE *table) {
    VALUE_TYPE lhsType;
    VALUE_TYPE rhsType;
    bool lhsCheck = checkATOMIC_EXPRESSION(expression.lhs, &lhsType, table);
    bool rhsCheck = checkATOMIC_EXPRESSION(expression.rhs, &rhsType, table);
    bool bothSame = lhsType == rhsType;
    bool bothBoolean = lhsType == VALUE_TYPE_boolean && bothSame;
    bool bothInteger = lhsType == VALUE_TYPE_integer && bothSame;
    switch (expression.op) {
        case OP_and:
        case OP_or:
        case OP_implies:
        case OP_xor:
            *expressionType = VALUE_TYPE_boolean;
            return lhsCheck && rhsCheck && bothBoolean;
        case OP_add:
        case OP_subtract:
            *expressionType = VALUE_TYPE_integer;
            return lhsCheck && rhsCheck && bothInteger;
        case OP_equals:
        case OP_distinct:
            *expressionType = VALUE_TYPE_boolean;
            return lhsCheck && rhsCheck && bothSame;
        default:
            return false;
    }
}

bool checkUNARY_EXPRESSION(UNARY_EXPRESSION expression, VALUE_TYPE *expressionType, SYMBOL_TABLE *table) {
    VALUE_TYPE operandType;
    bool operandCheck = checkATOMIC_EXPRESSION(expression.operand, &operandType, table);
    switch (expression.op) {
        case OP_not:
            *expressionType = VALUE_TYPE_boolean;
            return operandCheck && operandType == VALUE_TYPE_boolean;
        case OP_subtract:
            *expressionType = VALUE_TYPE_integer;
            return operandCheck && operandType == VALUE_TYPE_integer;
        default:
            return false;
    }
}

bool checkTERNARY_EXPRESSION(TERNARY_EXPRESSION expression, VALUE_TYPE *expressionType, SYMBOL_TABLE *table) {

}

bool checkATOMIC_EXPRESSION(ATOMIC_EXPRESSION expression, VALUE_TYPE *expressionType, SYMBOL_TABLE *table) {
    switch (expression.type) {
        case A_id:
            *expressionType = getVar(table, expression.contents.identifier.id).type;
            return true;
        case A_val:
            *expressionType = expression.contents.value.type;
            return true;
        default:
            return false;
    }
}