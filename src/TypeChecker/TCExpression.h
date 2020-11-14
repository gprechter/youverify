//
// Created by Griffin Prechter on 10/30/20.
//

#ifndef YOUVERIFY_EXPRESSION_H

#include <stdbool.h>
#include "AST/Expression.h"
#include "Analyze/SymbolTable.h"

bool checkEXPRESSION(EXPRESSION expression, VALUE_TYPE *expressionType, SYMBOL_TABLE *table);

bool checkBINARY_EXPRESSION(BINARY_EXPRESSION expression, VALUE_TYPE *expressionType, SYMBOL_TABLE *table);

bool checkUNARY_EXPRESSION(UNARY_EXPRESSION expression, VALUE_TYPE *expressionType, SYMBOL_TABLE *table);

bool checkTERNARY_EXPRESSION(TERNARY_EXPRESSION expression, VALUE_TYPE *expressionType, SYMBOL_TABLE *table);

bool checkATOMIC_EXPRESSION(ATOMIC_EXPRESSION expression, VALUE_TYPE *expressionType, SYMBOL_TABLE *table);

#endif //YOUVERIFY_EXPRESSION_H
