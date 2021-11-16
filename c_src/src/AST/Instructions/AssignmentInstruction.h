//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_ASSIGNMENTINSTRUCTION_H
#define YOUVERIFY_ASSIGNMENTINSTRUCTION_H

#include "AST/Identifier.h"
#include "AST/Expression.h"

typedef enum _AssignmentInstructionLHS {AI_variable, AI_array_elem, AI_field, AI_deref} AssignmentInstructionLHS;

typedef struct assignmentinstruction {
    AssignmentInstructionLHS lhsType;
    union AssignmentInstructionDestination {
        Identifier id;
        ARRAY_ACCESS_EXPRESSION arrayAccessExpression;
        FIELD_ACCESS_EXPRESSION fieldAccessExpression;
        DEREFERENCE_EXPRESSION dereferenceExpression;
    } destination;
    EXPRESSION expression;
} ASSIGNMENT_INSTRUCTION;

#endif //YOUVERIFY_ASSIGNMENTINSTRUCTION_H
