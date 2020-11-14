//
// Created by Griffin Prechter on 10/30/20.
//

#include <stdio.h>
#include "TCInstruction.h"

bool checkINSTRUCTION(INSTRUCTION instruction, SYMBOL_TABLE *table) {
    switch (instruction.type) {
        case I_declaration:
            return checkDECLARATION_INSTRUCTION(instruction.contents.declarationInstruction, table);
        case I_assignment:
            return checkASSIGNMENT_INSTRUCTION(instruction.contents.assignmentInstruction,table);
        case I_goto:
            return checkGOTO_INSTRUCTION(instruction.contents.gotoInstruction,table);
        default:
            return false;
    }
}

bool checkGOTO_INSTRUCTION(GOTO_INSTRUCTION instruction, SYMBOL_TABLE *table) {
    VALUE_TYPE expressionType;
    return checkEXPRESSION(instruction.predicate, &expressionType, table) && expressionType == VALUE_TYPE_boolean;
}

bool checkASSIGNMENT_INSTRUCTION(ASSIGNMENT_INSTRUCTION instruction, SYMBOL_TABLE *table) {
    VALUE_TYPE expressionType;
    return checkEXPRESSION(instruction.expression, &expressionType, table) && getVar(table, instruction.id.id).type == expressionType;
}

bool checkDECLARATION_INSTRUCTION(DECLARATION_INSTRUCTION instruction, SYMBOL_TABLE *table) {
    return true;
}