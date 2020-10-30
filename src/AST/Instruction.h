//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_INSTRUCTION_H
#define YOUVERIFY_INSTRUCTION_H

#include "Instructions/AssignmentInstruction.h"
#include "Instructions/GotoInstruction.h"
#include "Instructions/DeclarationInstruction.h"

typedef int PC;

typedef enum instructiontype {I_declaration, I_assignment, I_goto} INSTRUCTION_TYPE;

typedef struct inst {
    INSTRUCTION_TYPE type;
    union INSTRUCTION_CONTENTS {
        DECLARATION_INSTRUCTION declarationInstruction;
        ASSIGNMENT_INSTRUCTION assignmentInstruction;
        GOTO_INSTRUCTION gotoInstruction;
    } contents;
} INSTRUCTION;

INSTRUCTION newGOTO_INSTRUCTION(EXPRESSION predicate, IDENTIFIER destination);
INSTRUCTION newASSIGNMENT_INSTRUCTION(IDENTIFIER id, EXPRESSION expression);
INSTRUCTION newDECLARATION_INSTRUCTION(IDENTIFIER id, VALUE_TYPE type);

#endif //YOUVERIFY_INSTRUCTION_H
