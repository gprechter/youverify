//
// Created by Griffin Prechter on 1/2/21.
//

#ifndef YOUVERIFY_RT_VARIABLE_H
#define YOUVERIFY_RT_VARIABLE_H

#include "AST/Identifier.h"
#include "Analyze/SymbolTable.h"

typedef struct _RT_Variable {
    NAME_SCOPE scope;
    TYPE type;
    int index;
} RT_Variable;

RT_Variable newRT_Variable(Identifier identifier, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
#endif //YOUVERIFY_RT_VARIABLE_H
