//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_IDENTIFIER_H
#define YOUVERIFY_IDENTIFIER_H
#include "Value.h"

typedef struct identifier {
    VALUE_TYPE type;
    char *id;
} IDENTIFIER;

IDENTIFIER newIDENTIFIER(char *id, VALUE_TYPE type);
void freeIDENTIFIER(IDENTIFIER identifier);

#endif //YOUVERIFY_IDENTIFIER_H
