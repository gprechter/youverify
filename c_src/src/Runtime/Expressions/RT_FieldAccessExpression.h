//
// Created by Griffin Prechter on 2/1/21.
//

#ifndef YOUVERIFY_RT_FIELDACCESSEXPRESSION_H
#define YOUVERIFY_RT_FIELDACCESSEXPRESSION_H

#include "AST/Value.h"
#include "Runtime/RT_Variable.h"

typedef struct _RT_FieldAccessExpression {
    TYPE elemType;
    RT_Variable record;
    int offset;
} RT_FieldAccessExpression;

#endif //YOUVERIFY_RT_FIELDACCESSEXPRESSION_H
