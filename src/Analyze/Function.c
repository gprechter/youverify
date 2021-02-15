//
// Created by Griffin Prechter on 11/13/20.
//

#include "Function.h"
FUNCTION newFunction(Identifier name, int size, TYPE returnType, INSTRUCTION* body, SYMBOL_TABLE* symbolTable) {
    FUNCTION func;
    func.name = name;
    func.size = size;
    func.returnType = returnType;
    func.body = body;
    func.symbolTable = symbolTable;
    return func;
}

FUNCTION fillFunction(SYMBOL_TABLE* globalTable, int index, FUNCTION_DEFINE_INSTRUCTION instruction) {
    FUNCTION function;
    FunctionData* functionData = malloc(sizeof(FunctionData));
    functionData->numParameters = instruction.parameters->size;
    functionData->returnType = instruction.returnType;
    functionData->index = index;
    HM_put(globalTable->functions, instruction.name.id, functionData);
    function.name = instruction.name;
    function.symbolTable = createSymbolTable();
    function.symbolTable->parent = globalTable;
    function.returnType = instruction.returnType;
    function.rawBody = instruction.body;
    fillIdentifiers(function.symbolTable, instruction.declarations, instruction.parameters, NULL, &(functionData->parameterTypes));
    return function;
}