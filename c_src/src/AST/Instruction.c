//
// Created by Griffin Prechter on 10/29/20.
//

#include "Instruction.h"
#include <stdio.h>

INSTRUCTION newASSIGNMENT_INSTRUCTION_TO_IDENTIFIER(Identifier id, EXPRESSION expression) {
    INSTRUCTION i;
    i.type = I_assignment;
    i.label = NULL;
    ASSIGNMENT_INSTRUCTION c;
    c.lhsType = AI_variable;
    c.destination.id = id;
    c.expression = expression;
    i.contents.assignmentInstruction = c;
    return i;
}
INSTRUCTION newASSIGNMENT_INSTRUCTION_TO_ARRAY_ELEM(ARRAY_ACCESS_EXPRESSION arrayAccessExpression, EXPRESSION expression) {
    INSTRUCTION i;
    i.type = I_assignment;
    i.label = NULL;
    ASSIGNMENT_INSTRUCTION c;
    c.lhsType = AI_array_elem;
    c.destination.arrayAccessExpression = arrayAccessExpression;
    c.expression = expression;
    i.contents.assignmentInstruction = c;
    return i;
}

INSTRUCTION newASSIGNMENT_INSTRUCTION_TO_FIELD(FIELD_ACCESS_EXPRESSION fieldAccessExpression, EXPRESSION expression) {
    INSTRUCTION i;
    i.type = I_assignment;
    i.label = NULL;
    ASSIGNMENT_INSTRUCTION c;
    c.lhsType = AI_field;
    c.destination.fieldAccessExpression = fieldAccessExpression;
    c.expression = expression;
    i.contents.assignmentInstruction = c;
    return i;
}

INSTRUCTION newASSIGNMENT_INSTRUCTION_TO_REFERENCE(DEREFERENCE_EXPRESSION dereferenceExpression, EXPRESSION expression) {
    INSTRUCTION i;
    i.type = I_assignment;
    i.label = NULL;
    ASSIGNMENT_INSTRUCTION c;
    c.lhsType = AI_deref;
    c.destination.dereferenceExpression = dereferenceExpression;
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

INSTRUCTION newDECLARATION_INSTRUCTION(Identifier id, TYPE type) {
    INSTRUCTION i;
    i.type = I_declaration;
    i.label = NULL;
    DECLARATION_INSTRUCTION d;
    d.identifier = id;
    d.type = type;
    i.contents.declarationInstruction = d;
    return i;
}

INSTRUCTION newRETURN_INSTRUCTION(EXPRESSION expression) {
    INSTRUCTION i;
    i.type = I_return;
    i.label = NULL;
    RETURN_INSTRUCTION r;
    r.expression = expression;
    i.contents.returnInstruction = r;
    return i;
}

INSTRUCTION newFUNCTION_DEFINE_INSTRUCTION(Identifier name, QueuePtr parameters, TYPE returnType, QueuePtr declarations, QueuePtr body) {
    INSTRUCTION i;
    i.type = I_function;
    i.label = NULL;
    FUNCTION_DEFINE_INSTRUCTION instruction;
    instruction.name = name;
    instruction.parameters = parameters;
    instruction.returnType = returnType;
    instruction.declarations = declarations;
    instruction.body = body;
    i.contents.functionDefineInstruction = instruction;
    return i;
}