//
// Created by Griffin Prechter on 11/13/20.
//

#include <TypeChecker/TCInstruction.h>
#include "Transform.h"
#include "Program.h"

INSTRUCTION *makeProgramArray(QueuePtr instructions, int *programSize) {
    INSTRUCTION *program = malloc(sizeof(INSTRUCTION) * instructions->size);
    *programSize = instructions->size;
    INSTRUCTION instruction;
    int i = 0;
    while(!isEmpty(instructions)) {
        instruction = *((INSTRUCTION *)pop(instructions));
        program[i++] = instruction;
    }
    return program;
}


void getLabelHashMap(INSTRUCTION *program, int programSize, SYMBOL_TABLE *table) {
    HashMap *hashMap = newHashMap();
    int num = 0;
    int i;
    for (i = 0; i < programSize; i++) {
        char * label = program[i].label;
        if (label != NULL)
            num++;
        printf("LABEL: %s\n", label);
    }
    int *destinations = malloc(sizeof(int)*num);
    num = 0;
    for (i = 0; i < programSize; i++) {
        char * label = program[i].label;
        if (label != NULL)
            HM_put(hashMap, label, num);
            destinations[num] = i;
            num++;
    }
    table->numLabels = num;
    table->labels = hashMap;
    table->destinations = destinations;
}

INSTRUCTION *generateAndCheckProgramArray(QueuePtr instructions, SYMBOL_TABLE *table, int *programSize) {
    INSTRUCTION *program = makeProgramArray(instructions, programSize);
    getLabelHashMap(program,*programSize,  table);
    INSTRUCTION instruction;
    int i;
    for(i = 0; i < *programSize; i++) {
        instruction = program[i];
        if (!checkINSTRUCTION(instruction, table)) {
            printf("Instruction: %d failed typechecking", i);
        }
        program[i] = transformINSTRUCTION(instruction, table);
    }
    return program;
}