//
// Created by Griffin Prechter on 11/24/20.
//

#ifndef YOUVERIFY_FUNCTIONCALLEXPRESSION_H
#define YOUVERIFY_FUNCTIONCALLEXPRESSION_H

#include "AST/Identifier.h"
#include "Queue.h"

typedef struct function_call_expression {
    Identifier name;
    QueuePtr parameters;
} FUNCTION_CALL_EXPRESSION;

#endif //YOUVERIFY_FUNCTIONCALLEXPRESSION_H
