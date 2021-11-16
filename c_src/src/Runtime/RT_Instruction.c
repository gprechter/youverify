//
// Created by Griffin Prechter on 1/6/21.
//

#include "RT_Instruction.h"

RT_AssignmentInstruction newRT_AssignmentInstruction(ASSIGNMENT_INSTRUCTION instruction, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_AssignmentInstruction rtAssignmentInstruction;
    rtAssignmentInstruction.type = instruction.lhsType;
    switch (instruction.lhsType) {
        case AI_variable: {
            rtAssignmentInstruction.destination.variable = newRT_Variable(instruction.destination.id, symbolTable, lexicalScope);
            rtAssignmentInstruction.expression = newRT_Expression(instruction.expression, symbolTable, lexicalScope);
            return rtAssignmentInstruction;
        }
        case AI_array_elem: {
            rtAssignmentInstruction.destination.arrayAccessExpression = newRT_ArrayAccessExpression(instruction.destination.arrayAccessExpression, symbolTable, lexicalScope);
            rtAssignmentInstruction.expression = newRT_Expression(instruction.expression, symbolTable, lexicalScope);
            return rtAssignmentInstruction;
        }
        case AI_field: {
            rtAssignmentInstruction.destination.fieldAccessExpression = newRT_FieldAccessExpression(instruction.destination.fieldAccessExpression, symbolTable, lexicalScope);
            rtAssignmentInstruction.expression = newRT_Expression(instruction.expression, symbolTable, lexicalScope);
            return rtAssignmentInstruction;
        }
        case AI_deref: {
            rtAssignmentInstruction.destination.dereferenceExpression = newRT_DereferenceExpression(instruction.destination.dereferenceExpression, symbolTable, lexicalScope);
            rtAssignmentInstruction.expression = newRT_Expression(instruction.expression, symbolTable, lexicalScope);
            return rtAssignmentInstruction;
        }
    }
}
RT_GotoInstruction newRT_GotoInstruction(GOTO_INSTRUCTION instruction, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_GotoInstruction gotoInstruction;
    LabelData* labelData;
    HM_get(symbolTable->labels, instruction.destination.id, &labelData);
    gotoInstruction.pc_next = labelData->pc_nxt;
    gotoInstruction.predicate = newRT_Expression(instruction.predicate, symbolTable, lexicalScope);
    return gotoInstruction;
}

RT_ReturnInstruction newRT_ReturnInstruction(RETURN_INSTRUCTION instruction, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_ReturnInstruction returnInstruction;
    returnInstruction.expression = newRT_Expression(instruction.expression, symbolTable, lexicalScope);
    return returnInstruction;
}

RT_Instruction newRT_Instruction(INSTRUCTION instruction, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_Instruction rtInstruction;
    switch (instruction.type) {
        case I_assignment: {
            rtInstruction.type = RT_assignment;
            rtInstruction.contents.assignmentInstruction = newRT_AssignmentInstruction(instruction.contents.assignmentInstruction, symbolTable, lexicalScope);
            return rtInstruction;
        }
        case I_return: {
            rtInstruction.type = RT_return;
            rtInstruction.contents.returnInstruction = newRT_ReturnInstruction(instruction.contents.returnInstruction, symbolTable, lexicalScope);
            return rtInstruction;
        }
        case I_goto: {
            rtInstruction.type = RT_goto;
            rtInstruction.contents.gotoInstruction = newRT_GotoInstruction(instruction.contents.gotoInstruction, symbolTable, lexicalScope);
            return rtInstruction;
        }
        default:
            return rtInstruction;
    }
}