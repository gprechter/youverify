//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_ASSIGNMENTINSTRUCTION_H
#define YOUVERIFY_ASSIGNMENTINSTRUCTION_H

#include "AST/Expression.h"
#include "AST/Expressions/AtomicExpression.h"

typedef struct assignmentinstruction {
    Identifier id;
    EXPRESSION expression;
} ASSIGNMENT_INSTRUCTION;

#endif //YOUVERIFY_ASSIGNMENTINSTRUCTION_H
