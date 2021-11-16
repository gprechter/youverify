//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_ATOMICEXPRESSION_H
#define YOUVERIFY_ATOMICEXPRESSION_H

#include "AST/Identifier.h"
#include "AST/Value.h"

typedef enum atomicexpressiontype {A_id, A_val} ATOMIC_EXPRESSION_TYPE;

typedef struct atomicexpression {
    ATOMIC_EXPRESSION_TYPE type;
    union ATOMIC_EXPRESSION_CONTENTS {
        Identifier identifier;
        VALUE value;
    } contents;
} ATOMIC_EXPRESSION;

ATOMIC_EXPRESSION newATOMIC_EXPRESSION_IDENTIFIER(Identifier identifier);
ATOMIC_EXPRESSION newATOMIC_EXPRESSION_VALUE(VALUE value);

#endif //YOUVERIFY_ATOMICEXPRESSION_H
