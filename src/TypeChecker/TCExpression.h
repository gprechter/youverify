//
// Created by Griffin Prechter on 10/30/20.
//

#ifndef YOUVERIFY_EXPRESSION_H

#include <stdbool.h>
#include "AST/Expression.h"

bool checkEXPRESSION(EXPRESSION expression, VALUE_TYPE *expressionType);

bool checkBINARY_EXPRESSION(BINARY_EXPRESSION expression, VALUE_TYPE *expressionType);

bool checkUNARY_EXPRESSION(UNARY_EXPRESSION expression, VALUE_TYPE *expressionType);

bool checkTERNARY_EXPRESSION(TERNARY_EXPRESSION expression, VALUE_TYPE *expressionType);

bool checkATOMIC_EXPRESSION(ATOMIC_EXPRESSION expression, VALUE_TYPE *expressionType);

#endif //YOUVERIFY_EXPRESSION_H
