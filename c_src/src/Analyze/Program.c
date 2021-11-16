//
// Created by Griffin Prechter on 11/13/20.
//

#include "Program.h"

INSTRUCTION *makeProgramArray(QueuePtr instructions, SYMBOL_TABLE* symbolTable, int *programSize) {
    INSTRUCTION *program = malloc(sizeof(INSTRUCTION) * instructions->size);
    *programSize = instructions->size;
    INSTRUCTION * instructionPtr;
    INSTRUCTION instruction;
    int i = 0;
    while(!isEmpty(instructions)) {
        instructionPtr = (INSTRUCTION *) pop(instructions);
        instruction = *(instructionPtr);
        free(instructionPtr);
        if (instruction.label != NULL) {
            addLabel(symbolTable, instruction.label, i);
        }
        program[i++] = instruction;
    }
    free(instructions);
    return program;
}

RT_Instruction *generateProgramArray(QueuePtr instructions, SYMBOL_TABLE *table, int *programSize, NAME_SCOPE scope) {
    INSTRUCTION *program = makeProgramArray(instructions, table, programSize);
    RT_Instruction* runtimeProgram = malloc(sizeof(RT_Instruction) * (*programSize));
    INSTRUCTION instruction;
    int i;
    for(i = 0; i < *programSize; i++) {
        instruction = program[i];
        /* TODO: Integrate Type Checking here!
        if (!checkINSTRUCTION(instruction, table)) {
            printf("Instruction: %d failed typechecking", i);
        }
        */
        bool isValid;
        runtimeProgram[i] = newRT_Instruction(instruction, table, scope);
    }
    free(program);
    return runtimeProgram;
}