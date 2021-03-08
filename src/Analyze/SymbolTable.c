//
// Created by Griffin Prechter on 11/13/20.
//

#include "SymbolTable.h"
#include "AST/Instruction.h"
#include "Utilities.h"
#include "Function.h"

SYMBOL_TABLE *newSymbolTable() {
    SYMBOL_TABLE *symbolTable = malloc(sizeof(SYMBOL_TABLE));
    symbolTable->functions = newHashMap();
    symbolTable->identifiers = newHashMap();
    symbolTable->labels = newHashMap();
    symbolTable->LocalArrayBindings = newLinkedList();
    symbolTable->parent = NULL;
    return symbolTable;
}

SYMBOL_TABLE *newGlobalSymbolTable(QueuePtr declarations, FUNCTION** functions, int* numFunctions) {
    SYMBOL_TABLE* globalTable = newSymbolTable();
    QueuePtr functionsQueue = newQueue();
    fillIdentifiers(globalTable, declarations, NULL, functionsQueue, NULL);
    *numFunctions = functionsQueue->size;
    if (!isEmpty(functionsQueue)) {
        *functions = malloc(sizeof(FUNCTION) * functionsQueue->size);
    } else {
        *functions = NULL;
    }
    int f_i = 0;
    while (!isEmpty(functionsQueue)) {
        FUNCTION_DEFINE_INSTRUCTION functionDefineInstruction = ((INSTRUCTION*) pop(functionsQueue))->contents.functionDefineInstruction;
        *functions[f_i] = fillFunction(globalTable, f_i, functionDefineInstruction);
        f_i++;
    }
    return globalTable;
}

void addLabel(SYMBOL_TABLE* symbolTable, char* str, int instNum) {
    LabelData *labelData = malloc(sizeof(LabelData));
    labelData->pc_nxt = instNum;
    HM_put(symbolTable->labels, str, (void *) labelData);
}

void fillIdentifiers(SYMBOL_TABLE* symbolTable, QueuePtr declarations, QueuePtr parameters, QueuePtr functions, TYPE** parameterTypes) {
    INSTRUCTION *instruction;
    IdentifierData* identifierData;
    int d_i = 0;
    if (parameters != NULL) {
        TYPE* parameterTypeArray = malloc(sizeof(TYPE) * parameters->size);
        *parameterTypes = parameterTypeArray;
        int t_i = 0;
        while (!isEmpty(parameters)) {
            instruction = ((INSTRUCTION *) pop(parameters));
            DECLARATION_INSTRUCTION inst = instruction->contents.declarationInstruction;
            identifierData = malloc(sizeof(IdentifierData));
            d_i = d_i + rUB(inst.type.bits);
            identifierData->index = d_i;
            identifierData->type = inst.type;
            HM_put(symbolTable->identifiers, inst.identifier.id, (void *) identifierData);
            parameterTypeArray[t_i] = inst.type;
            t_i++;
        }
    }

    while(!isEmpty(declarations)) {
        instruction = ((INSTRUCTION *)pop(declarations));
        if (instruction->type == I_declaration) {
            DECLARATION_INSTRUCTION inst = instruction->contents.declarationInstruction;
            identifierData = malloc(sizeof(IdentifierData));
            d_i = d_i + rUB(inst.type.bits);
            identifierData->index = d_i;
            identifierData->type = inst.type;
            if (identifierData->type.id == TID_array) {
                struct LocalArrayBindingInfo* info = malloc(sizeof(struct LocalArrayBindingInfo));
                info->arrayMeta = identifierData->type.metadata.array_info;
                info->variableIndex = identifierData->index;
                addFirst(symbolTable->LocalArrayBindings, info);
            }
            HM_put(symbolTable->identifiers, inst.identifier.id, (void *) identifierData);
        } else {
            push(functions, (void *) instruction);
        }
    }
    symbolTable->totalRequiredBits = d_i;
}

FUNCTION fillFunction(SYMBOL_TABLE* globalTable, int index, FUNCTION_DEFINE_INSTRUCTION instruction) {
    FUNCTION function;
    FunctionData* functionData = malloc(sizeof(FunctionData));
    functionData->numParameters = instruction.parameters->size;
    functionData->returnType = instruction.returnType;
    functionData->index = index;
    HM_put(globalTable->functions, instruction.name.id, functionData);
    function.name = instruction.name;
    function.symbolTable = newSymbolTable();
    function.symbolTable->parent = globalTable;
    function.returnType = instruction.returnType;
    function.rawBody = instruction.body;
    fillIdentifiers(function.symbolTable, instruction.declarations, instruction.parameters, NULL, &(functionData->parameterTypes));
    return function;
}

bool getIdentifierData(SYMBOL_TABLE *table, char *str, IdentifierData** data) {
    return HM_get(table->identifiers, str, data);
}

void freeSymbolTable(SYMBOL_TABLE *table) {

}