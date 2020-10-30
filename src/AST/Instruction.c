//
// Created by Griffin Prechter on 10/29/20.
//

#include "Instruction.h"

INSTRUCTION newASSIGNMENT_INSTRUCTION(IDENTIFIER id, EXPRESSION expression) {
    INSTRUCTION i;
    i.type = I_assignment;
    ASSIGNMENT_INSTRUCTION c;
    c.id = id;
    c.expression = expression;
    i.contents.assignmentInstruction = c;
    return i;
}

INSTRUCTION newGOTO_INSTRUCTION(EXPRESSION predicate, IDENTIFIER destination) {
    INSTRUCTION i;
    i.type = I_goto;
    GOTO_INSTRUCTION c;
    c.predicate = predicate;
    c.destination = destination;
    i.contents.gotoInstruction = c;
    return i;
}