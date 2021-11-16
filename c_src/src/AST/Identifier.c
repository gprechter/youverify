//
// Created by Griffin Prechter on 10/29/20.
//

#include <stdlib.h>
#include "Identifier.h"

Identifier newIDENTIFIER(char *id) {
    Identifier newID;
    newID.id = id;
    newID.index = -1;
    newID.scope = local;
    return newID;
}

void freeIDENTIFIER(Identifier identifier) {
    free(identifier.id);
}
