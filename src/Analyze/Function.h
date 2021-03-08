//
// Created by Griffin Prechter on 11/13/20.
//

#ifndef YOUVERIFY_FUNCTION_H
#define YOUVERIFY_FUNCTION_H

#include <Queue.h>
#include "AST/Identifier.h"
#include "Runtime/RT_Instruction.h"


typedef struct function {
    Identifier name;
    int size;
    TYPE returnType;
    QueuePtr rawBody;
    RT_Instruction* body;
    SYMBOL_TABLE* symbolTable;
} FUNCTION;

FUNCTION newFunction(Identifier name, int size, TYPE returnType, INSTRUCTION* body, SYMBOL_TABLE* symbolTable);
FUNCTION fillFunction(SYMBOL_TABLE* globalTable, int index, FUNCTION_DEFINE_INSTRUCTION instruction);
#endif //YOUVERIFY_FUNCTION_H
