//
// Created by Griffin Prechter on 11/24/20.
//

#include "Main.h"
#include "y.tab.h"

#include "parse.h"
#include "AST/Value.h"
#include "Analyze/SymbolTable.h"
#include "Analyze/Function.h"
#include "Analyze/Program.h"
#include "Memory.h"
#include "Execution.h"
#include "inttypes.h"

int main(int argc, char **argv) {
    PROGRAM *prgm;
    initialize();
    if (argc > 1) {
        prgm = parseProgram(argv[1]);
    }
    SYMBOL_TABLE* globalTable = createSymbolTable();
    QueuePtr functions = newQueue();
    fillIdentifiers(globalTable, prgm->declarations, NULL, functions, NULL);
    IdentifierData* data;
    //printf("Index for \'done\'(%d): %d, type: %d\n", getIdentifierData(globalTable, "result", &data),  data->index, data->valueType);
    int programSize;
    int functionSize = functions->size;
    FUNCTION* functionData;
    if (!isEmpty(functions)) {
        functionData = malloc(sizeof(FUNCTION) * functions->size);
    } else {
        functionData = NULL;
    }
    int f_i = 0;
    while (!isEmpty(functions)) {
        FUNCTION_DEFINE_INSTRUCTION functionDefineInstruction = ((INSTRUCTION*) pop(functions))->contents.functionDefineInstruction;
        functionData[f_i] = fillFunction(globalTable, f_i, functionDefineInstruction);
        f_i++;
    }
    initializeOperators();
    RT_Instruction* program = generateProgramArray(prgm->statements, globalTable, &programSize, global);
    for (int i = 0; i < functionSize; i++) {
        functionData[i].body = generateProgramArray(functionData[i].rawBody, functionData[i].symbolTable, &functionData[i].size, local);
    }
    //printf("Number of Labels: %d\n", globalTable->labels->numElements);

    int pc = 0;

    RuntimeEnvironment *environment = newRuntimeEnvironment(2048, globalTable);
    environment->functions = functionData;
    int i;
    while(pc < programSize) {
        if (program[pc].type == RT_assignment) {
            pc = executeAssignment(pc, program[pc].contents.assignmentInstruction, environment);
        } else {
            pc = executeBranch(pc, program[pc].contents.gotoInstruction, environment);
        }
    }
    if (argc <= 2) {
        for (i = (32 - 1); i >= 0; i--) {
            printf("0x%016" PRIx64 " || %08x", ((char *) environment->memory + i * 4),
                   *(((int *) environment->memory) + i));
            printf(((char *) environment->memory + i * 4) == environment->sp ? "<- sp\n" : "\n");
        }

    }
    IdentifierData* resultData;

    if (argc > 2 && getIdentifierData(globalTable, argv[2], &resultData)) {
        printf("%s: 0x%016" PRIx64, argv[2], *((long *) getGlobalVar(resultData->index / 32, environment)));
    }
    return 0;
    //freeSymbolTable(table);
}