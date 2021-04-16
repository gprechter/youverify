//
// Created by Griffin Prechter on 11/24/20.
//

#include "Main.h"
#include "parse.h"
#include "y.tab.h"
#include "AST/Value.h"
#include "Analyze/SymbolTable.h"
#include "Analyze/Function.h"
#include "Analyze/Program.h"
#include "Memory.h"
#include "Execution.h"
#include "inttypes.h"
#include "Analyze/HashMap.h"

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
    RT_Environment environment = createRT_Environment(NULL, globalTable->totalVariables, functions, global);
    environment.frameType = global;
    int i;
    while(pc < programSize) {
        if (program[pc].type == RT_assignment) {
            pc = executeAssignment(pc, program[pc].contents.assignmentInstruction, environment);
        } else {
            pc = executeBranch(pc, program[pc].contents.gotoInstruction, environment);
        }
    }
    RT_Value *global_variables = environment.variables;
    int num_variables = globalTable->totalVariables;
    QueuePtr keys = HM_getKeys(globalTable->identifiers);
    printf("{\n");
    while (!isEmpty(keys)) {
        char *name = (char *) pop(keys);
        IdentifierData *identifierData;
        bool exists = HM_get(globalTable->identifiers, name, &identifierData);
        if (exists) {
            switch (identifierData->type.id) {
                case TID_integer: {
                    printf("\"%s\": %d", name, *((int *)global_variables[identifierData->index].content));
                    break;
                }
                case TID_boolean: {
                    printf("\"%s\": %s", name, *((bool *)global_variables[identifierData->index].content) ? "true" : "false");
                }
            }
            printf("%s\n", !isEmpty(keys) ? "," : "");
        }
    }
    printf("}");
    return 0;
    //freeSymbolTable(table);
}