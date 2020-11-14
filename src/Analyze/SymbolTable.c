//
// Created by Griffin Prechter on 11/13/20.
//

#include "SymbolTable.h"
SYMBOL_TABLE *createSymbolTable(QueuePtr declarations) {
    SYMBOL_TABLE *globalSymbolTable = malloc(sizeof(SYMBOL_TABLE));
    globalSymbolTable->num = declarations->size;
    HashMap *hashMap = newHashMap();
    VARIABLE *variables = malloc(sizeof(VARIABLE) * declarations->size);
    int i = 0;
    INSTRUCTION *instruction;
    while(!isEmpty(declarations)) {
        instruction = ((INSTRUCTION *)pop(declarations));
        if (instruction->type == I_declaration) {
            DECLARATION_INSTRUCTION inst = instruction->contents.declarationInstruction;
            variables[i].type = inst.type;
            HM_put(hashMap, inst.identifier.id, i++);
        } else {
            printf("FUNCTION \'%s\' WITH:\n", instruction->contents.functionDefineInstruction.name.id);
            printf("\t %d Declarations,\n",instruction->contents.functionDefineInstruction.declarations->size);
            printf("\t %d Statements,\n",instruction->contents.functionDefineInstruction.body->size);
        }

    }
    globalSymbolTable->table = hashMap;
    globalSymbolTable->variables = variables;
    globalSymbolTable->labels = NULL;
    return  globalSymbolTable;
}
VARIABLE getVar(SYMBOL_TABLE *table, char *str) {
    return table->variables[HM_get(table->table, str)];
}

int getIndex(SYMBOL_TABLE *table, char *str) {
    return HM_get(table->table, str);
}

void setVar(SYMBOL_TABLE *table, char *str, VALUE value) {
    table->variables[HM_get(table->table, str)] = value;
}

VARIABLE getVarByIndex(SYMBOL_TABLE *table, int index) {
    return table->variables[index];
}

void setVarByIndex(SYMBOL_TABLE *table, int index, VALUE value) {
    table->variables[index] = value;
}

void freeSymbolTable(SYMBOL_TABLE *table) {
    free(table->variables);
    freeHashMap(table->table);
    free(table);

}