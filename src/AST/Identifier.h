//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_IDENTIFIER_H
#define YOUVERIFY_IDENTIFIER_H
#include "Value.h"

typedef struct identifier {
    char *id;
    int index;
} Identifier;

Identifier newIDENTIFIER(char *id);
void freeIDENTIFIER(Identifier identifier);

#endif //YOUVERIFY_IDENTIFIER_H
