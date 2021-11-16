//
// Created by Griffin Prechter on 11/13/20.
//

#ifndef YOUVERIFY_SYMBOLTABLE_H
#define YOUVERIFY_SYMBOLTABLE_H


#include <AST/Instructions/FunctionDefineInstruction.h>
#include "AST/Value.h"
#include "HashMap.h"
#include "LinkedList.h"
#include "Queue.h"

typedef struct function FUNCTION;
typedef struct _IdentifierData {
    int index;
    TYPE type;
} IdentifierData;

typedef struct _FunctionData {
    int index;
    TYPE returnType;
    int numParameters;
    TYPE* parameterTypes;
} FunctionData;

typedef struct _LabelData {
    int pc_nxt;
} LabelData;

struct LocalArrayBindingInfo {
    int variableIndex;
    ArrayMeta arrayMeta;
};

typedef struct symbolTable {
    HashMap* identifiers;
    LinkedListPtr LocalArrayBindings;
    int totalRequiredBits;
    HashMap* functions;
    HashMap* labels;
    struct symbolTable *parent;
} SYMBOL_TABLE;

void addLabel(SYMBOL_TABLE* symbolTable, char* str, int instNum);

SYMBOL_TABLE *newSymbolTable();
SYMBOL_TABLE *newGlobalSymbolTable(QueuePtr declarations, FUNCTION** functions, int* numFunctions);

void fillIdentifiers(SYMBOL_TABLE* symbolTable, QueuePtr declarations, QueuePtr parameters, QueuePtr functions, TYPE** parameterTypes);
FUNCTION fillFunction(SYMBOL_TABLE* globalTable, int index, FUNCTION_DEFINE_INSTRUCTION instruction);


bool getIdentifierData(SYMBOL_TABLE *table, char *str, IdentifierData** data);
void freeSymbolTable(SYMBOL_TABLE *table);
#endif //YOUVERIFY_SYMBOLTABLE_H
