//
// Created by Griffin Prechter on 10/29/20.
//

#include "AtomicExpression.h"

ATOMIC_EXPRESSION newATOMIC_EXPRESSION_IDENTIFIER(IDENTIFIER identifier) {
    ATOMIC_EXPRESSION s;
    s.type = A_id;
    s.contents.identifier = identifier;
    return s;
}
ATOMIC_EXPRESSION newATOMIC_EXPRESSION_VALUE(VALUE value) {
    ATOMIC_EXPRESSION s;
    s.type = A_val;
    s.contents.value = value;
    return s;
}