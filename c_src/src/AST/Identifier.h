//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_IDENTIFIER_H
#define YOUVERIFY_IDENTIFIER_H
#include "Value.h"

typedef enum scope {local, global} NAME_SCOPE;

typedef struct identifier {
    NAME_SCOPE scope;
    char *id;
    int index;
    TYPE type;
} Identifier;

Identifier newIDENTIFIER(char *id);
void freeIDENTIFIER(Identifier identifier);

#endif //YOUVERIFY_IDENTIFIER_H
