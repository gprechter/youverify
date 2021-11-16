//
// Created by Griffin Prechter on 1/6/21.
//

#ifndef YOUVERIFY_RT_INSTRUCTION_H
#define YOUVERIFY_RT_INSTRUCTION_H

#include "AST/Instruction.h"
#include "Runtime/Instructions/RT_AssignmentInstruction.h"
#include "Runtime/Instructions/RT_GotoInstruction.h"
#include "Runtime/Instructions/RT_ReturnInstruction.h"

typedef enum rtinstructiontype {RT_assignment, RT_goto, RT_return} RT_INSTRUCTION_TYPE;

typedef struct _RT_Instruction {
    RT_INSTRUCTION_TYPE type;
    union RT_InstructionContents {
        RT_AssignmentInstruction assignmentInstruction;
        RT_GotoInstruction gotoInstruction;
        RT_ReturnInstruction returnInstruction;
    } contents;
} RT_Instruction;

RT_AssignmentInstruction newRT_AssignmentInstruction(ASSIGNMENT_INSTRUCTION instruction, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
RT_GotoInstruction newRT_GotoInstruction(GOTO_INSTRUCTION instruction, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
RT_ReturnInstruction newRT_ReturnInstruction(RETURN_INSTRUCTION instruction, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);

RT_Instruction newRT_Instruction(INSTRUCTION instruction, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);

#endif //YOUVERIFY_RT_INSTRUCTION_H
