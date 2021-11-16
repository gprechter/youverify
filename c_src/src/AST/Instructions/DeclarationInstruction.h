//
// Created by Griffin Prechter on 10/30/20.
//

#ifndef YOUVERIFY_DECLARATIONINSTRUCTION_H
#define YOUVERIFY_DECLARATIONINSTRUCTION_H

#include "AST/Expression.h"
#include "AST/Expressions/AtomicExpression.h"

typedef struct declinstruction {
    Identifier identifier;
    TYPE type;
} DECLARATION_INSTRUCTION;

#endif //YOUVERIFY_DECLARATIONINSTRUCTION_H
