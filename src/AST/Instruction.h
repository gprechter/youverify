//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_INSTRUCTION_H
#define YOUVERIFY_INSTRUCTION_H

#include "Instructions/AssignmentInstruction.h"
#include "Instructions/GotoInstruction.h"

typedef int PC;

typedef enum instructiontype {I_assignment, I_goto} INSTRUCTION_TYPE;

typedef struct inst {
    INSTRUCTION_TYPE type;
    union INSTRUCTION_CONTENTS {
        ASSIGNMENT_INSTRUCTION assignmentInstruction;
        GOTO_INSTRUCTION gotoInstruction;
    } contents;
} INSTRUCTION;

INSTRUCTION newGOTO_INSTRUCTION(EXPRESSION predicate, IDENTIFIER destination);
INSTRUCTION newASSIGNMENT_INSTRUCTION(IDENTIFIER id, EXPRESSION expression);

#endif //YOUVERIFY_INSTRUCTION_H
