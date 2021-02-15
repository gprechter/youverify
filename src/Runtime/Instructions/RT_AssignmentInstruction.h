//
// Created by Griffin Prechter on 1/6/21.
//

#ifndef YOUVERIFY_RT_ASSIGNMENTINSTRUCTION_H
#define YOUVERIFY_RT_ASSIGNMENTINSTRUCTION_H

#include "Runtime/RT_Variable.h"
#include "Runtime/RT_Expression.h"

typedef struct _RT_AssignmentInstruction {
    AssignmentInstructionLHS type;
    union RT_AssignmentInstructionDesitnation {
        RT_Variable variable;
        RT_ArrayAccessExpression arrayAccessExpression;
        RT_FieldAccessExpression fieldAccessExpression;
        RT_DereferenceExpression dereferenceExpression;
    } destination;
    RT_Expression expression;
} RT_AssignmentInstruction;

#endif //YOUVERIFY_RT_ASSIGNMENTINSTRUCTION_H
