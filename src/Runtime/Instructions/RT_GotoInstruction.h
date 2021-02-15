//
// Created by Griffin Prechter on 1/6/21.
//

#ifndef YOUVERIFY_RT_GOTOINSTRUCTION_H
#define YOUVERIFY_RT_GOTOINSTRUCTION_H

#include "Runtime/RT_Expression.h"

typedef struct _RT_GotoInstruction {
    RT_Expression predicate;
    int pc_next;
} RT_GotoInstruction;

#endif //YOUVERIFY_RT_GOTOINSTRUCTION_H
