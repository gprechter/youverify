//
// Created by Griffin Prechter on 2/1/21.
//

#ifndef YOUVERIFY_FIELDACCESSEXPRESSION_H
#define YOUVERIFY_FIELDACCESSEXPRESSION_H

#include "AST/Identifier.h"

typedef struct fieldaccessexpression {
    Identifier record;
    Identifier field;
} FIELD_ACCESS_EXPRESSION;

#endif //YOUVERIFY_FIELDACCESSEXPRESSION_H
