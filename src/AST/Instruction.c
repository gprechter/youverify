//
// Created by Griffin Prechter on 10/29/20.
//

#include "Instruction.h"
#include <stdio.h>

INSTRUCTION newASSIGNMENT_INSTRUCTION(Identifier id, EXPRESSION expression) {
    INSTRUCTION i;
    i.type = I_assignment;
    i.label = NULL;
    ASSIGNMENT_INSTRUCTION c;
    c.id = id;
    c.expression = expression;
    i.contents.assignmentInstruction = c;
    return i;
}

INSTRUCTION newGOTO_INSTRUCTION(EXPRESSION predicate, Identifier destination) {
    INSTRUCTION i;
    i.type = I_goto;
    i.label = NULL;
    GOTO_INSTRUCTION c;
    c.predicate = predicate;
    c.destination = destination;
    i.contents.gotoInstruction = c;
    return i;
}

INSTRUCTION newDECLARATION_INSTRUCTION(Identifier id, VALUE_TYPE type) {
    INSTRUCTION i;
    i.type = I_declaration;
    i.label = NULL;
    DECLARATION_INSTRUCTION d;
    d.identifier = id;
    d.type = type;
    i.contents.declarationInstruction = d;
    return i;
}

INSTRUCTION newFUNCTION_DEFINE_INSTRUCTION(Identifier name, VALUE_TYPE returnType, QueuePtr declarations, QueuePtr body) {
    INSTRUCTION i;
    i.type = I_function;
    i.label = NULL;
    FUNCTION_DEFINE_INSTRUCTION instruction;
    instruction.name = name;
    instruction.returnType = returnType;
    instruction.declarations = declarations;
    instruction.body = body;
    i.contents.functionDefineInstruction = instruction;
    return i;
}