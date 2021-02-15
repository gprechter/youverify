//
// Created by Griffin Prechter on 1/2/21.
//

#include "RT_Variable.h"

RT_Variable newRT_Variable(Identifier identifier, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_Variable variable;

    IdentifierData* identifierData;
    bool exists = getIdentifierData(symbolTable, identifier.id, &identifierData);
    if (lexicalScope == global) {
        variable.scope = global;
    }
    else if (!exists && symbolTable->parent != NULL) {
        getIdentifierData(symbolTable->parent, identifier.id, &identifierData);
        variable.scope = global;
    } else {
        variable.scope = local;
    }
    variable.index = identifierData->index;
    variable.type = identifierData->type;
    return variable;
}