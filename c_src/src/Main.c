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
    FUNCTION* functions;
    int numFunctions;
    SYMBOL_TABLE* globalTable = newGlobalSymbolTable(prgm->declarations, &functions, &numFunctions);
    initializeOperators();

    int programSize;
    RT_Instruction* program = generateProgramArray(prgm->statements, globalTable, &programSize, global);
    for (int i = 0; i < numFunctions; i++) {
        functions[i].body = generateProgramArray(functions[i].rawBody, functions[i].symbolTable, &functions[i].size, local);
    }

    int pc = 0;

    RuntimeEnvironment *environment = newRuntimeEnvironment(32, globalTable);
    environment->functions = functions;
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