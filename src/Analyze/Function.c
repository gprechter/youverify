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