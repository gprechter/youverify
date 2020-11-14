//
// Created by Griffin Prechter on 11/13/20.
//

#ifndef YOUVERIFY_SYMBOLTABLE_H
#define YOUVERIFY_SYMBOLTABLE_H

#include "AST/Value.h"
#include "AST/Instruction.h"
#include "HashMap.h"
#include "Queue.h"
typedef VALUE VARIABLE;

typedef struct symbolTable {
    int num;
    HashMap *table;
    VARIABLE *variables;
    int numLabels;
    HashMap *labels;
    int *destinations;
} SYMBOL_TABLE;

SYMBOL_TABLE *createSymbolTable(QueuePtr declarations);
VARIABLE getVar(SYMBOL_TABLE *table, char *str);
int getIndex(SYMBOL_TABLE *table, char *str);
VARIABLE getVarByIndex(SYMBOL_TABLE *table, int index);
void setVarByIndex(SYMBOL_TABLE *table, int index, VALUE value);
void setVar(SYMBOL_TABLE *table, char *str, VALUE value);
void freeSymbolTable(SYMBOL_TABLE *table);
#endif //YOUVERIFY_SYMBOLTABLE_H
