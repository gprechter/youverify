//
// Created by Griffin Prechter on 11/6/20.
//

#ifndef YOUVERIFY_FUNCTIONDEFINEINSTRUCTION_H
#define YOUVERIFY_FUNCTIONDEFINEINSTRUCTION_H

#include "Queue.h"
#include "AST/Expressions/AtomicExpression.h"

typedef struct function_define_instruction {
    Identifier name;
    VALUE_TYPE returnType;
    QueuePtr declarations;
    QueuePtr body;
} FUNCTION_DEFINE_INSTRUCTION;
#endif //YOUVERIFY_FUNCTIONDEFINEINSTRUCTION_H
