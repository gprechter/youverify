//
// Created by Griffin Prechter on 10/29/20.
//

#include <stdlib.h>
#include "Identifier.h"

IDENTIFIER newIDENTIFIER(char *id, VALUE_TYPE type) {
    IDENTIFIER newID;
    newID.type = type;
    newID.id = id;
    return newID;
}

void freeIDENTIFIER(IDENTIFIER identifier) {
    free(identifier.id);
}