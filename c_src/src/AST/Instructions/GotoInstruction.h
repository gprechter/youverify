//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_GOTOINSTRUCTION_H
#define YOUVERIFY_GOTOINSTRUCTION_H

#include "AST/Expression.h"
#include "AST/Expressions/AtomicExpression.h"

typedef struct gotoinstruction {
    EXPRESSION predicate;
    Identifier destination;
} GOTO_INSTRUCTION;

#endif //YOUVERIFY_GOTOINSTRUCTION_H
