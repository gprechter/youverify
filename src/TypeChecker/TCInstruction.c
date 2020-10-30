//
// Created by Griffin Prechter on 10/30/20.
//

#include <stdio.h>
#include "TypeChecker/TCExpression.h"
#include "TypeChecker/TCInstruction.h"

bool checkINSTRUCTION(INSTRUCTION instruction) {
    switch (instruction.type) {
        case I_declaration:
            return checkDECLARATION_INSTRUCTION(instruction.contents.declarationInstruction);
        case I_assignment:
            return checkASSIGNMENT_INSTRUCTION(instruction.contents.assignmentInstruction);
        case I_goto:
            return checkGOTO_INSTRUCTION(instruction.contents.gotoInstruction);
        default:
            return false;
    }
}

bool checkGOTO_INSTRUCTION(GOTO_INSTRUCTION instruction) {
    VALUE_TYPE expressionType;
    return checkEXPRESSION(instruction.predicate, &expressionType) && expressionType == VALUE_TYPE_boolean;
}

bool checkASSIGNMENT_INSTRUCTION(ASSIGNMENT_INSTRUCTION instruction) {
    VALUE_TYPE expressionType;
    return checkEXPRESSION(instruction.expression, &expressionType) && instruction.id.type == expressionType;
}

bool checkDECLARATION_INSTRUCTION(DECLARATION_INSTRUCTION instruction) {
    return true;
}