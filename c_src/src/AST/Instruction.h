//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_INSTRUCTION_H
#define YOUVERIFY_INSTRUCTION_H

#include "Instructions/AssignmentInstruction.h"
#include "Instructions/FunctionDefineInstruction.h"
#include "Instructions/GotoInstruction.h"
#include "Instructions/DeclarationInstruction.h"
#include "Instructions/ReturnInstruction.h"
#include "AST/Expression.h"

typedef int PC;

typedef enum instructiontype {I_declaration, I_assignment, I_goto, I_function, I_return} INSTRUCTION_TYPE;

typedef struct inst {
    INSTRUCTION_TYPE type;
    char *label;
    union INSTRUCTION_CONTENTS {
        FUNCTION_DEFINE_INSTRUCTION functionDefineInstruction;
        DECLARATION_INSTRUCTION declarationInstruction;
        ASSIGNMENT_INSTRUCTION assignmentInstruction;
        GOTO_INSTRUCTION gotoInstruction;
        RETURN_INSTRUCTION returnInstruction;
    } contents;
} INSTRUCTION;

INSTRUCTION newGOTO_INSTRUCTION(EXPRESSION predicate, Identifier destination);
INSTRUCTION newASSIGNMENT_INSTRUCTION_TO_IDENTIFIER(Identifier id, EXPRESSION expression);
INSTRUCTION newASSIGNMENT_INSTRUCTION_TO_ARRAY_ELEM(ARRAY_ACCESS_EXPRESSION arrayAccessExpression, EXPRESSION expression);
INSTRUCTION newASSIGNMENT_INSTRUCTION_TO_FIELD(FIELD_ACCESS_EXPRESSION fieldAccessExpression, EXPRESSION expression);
INSTRUCTION newASSIGNMENT_INSTRUCTION_TO_REFERENCE(DEREFERENCE_EXPRESSION dereferenceExpression, EXPRESSION expression);
INSTRUCTION newDECLARATION_INSTRUCTION(Identifier id, TYPE type);
INSTRUCTION newRETURN_INSTRUCTION(EXPRESSION expression);
INSTRUCTION newFUNCTION_DEFINE_INSTRUCTION(Identifier name, QueuePtr parameters, TYPE returnType, QueuePtr declarations, QueuePtr body);

#endif //YOUVERIFY_INSTRUCTION_H
