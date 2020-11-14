//
// Created by Griffin Prechter on 11/13/20.
//

#include "Transform.h"

INSTRUCTION transformINSTRUCTION(INSTRUCTION instruction, SYMBOL_TABLE *table) {
    switch (instruction.type) {
        case I_declaration:
            instruction.contents.declarationInstruction = transformDECLARATION_INSTRUCTION(instruction.contents.declarationInstruction, table);
            return instruction;
        case I_assignment:
            instruction.contents.assignmentInstruction = transformASSIGNMENT_INSTRUCTION(instruction.contents.assignmentInstruction,table);
            return instruction;
        case I_goto:
             instruction.contents.gotoInstruction = transformGOTO_INSTRUCTION(instruction.contents.gotoInstruction,table);
             return instruction;
        default:
            return instruction;
    }
}

GOTO_INSTRUCTION transformGOTO_INSTRUCTION(GOTO_INSTRUCTION instruction, SYMBOL_TABLE *table) {
    instruction.predicate = transformEXPRESSION(instruction.predicate, table);
    instruction.destination.index = HM_get(table->labels, instruction.destination.id);
    return instruction;
}

ASSIGNMENT_INSTRUCTION transformASSIGNMENT_INSTRUCTION(ASSIGNMENT_INSTRUCTION instruction, SYMBOL_TABLE *table) {
    instruction.id.index = getIndex(table, instruction.id.id);
    instruction.expression = transformEXPRESSION(instruction.expression, table);
    return instruction;
}

DECLARATION_INSTRUCTION transformDECLARATION_INSTRUCTION(DECLARATION_INSTRUCTION instruction, SYMBOL_TABLE *table) {
    return instruction;
}

EXPRESSION transformEXPRESSION(EXPRESSION expression, SYMBOL_TABLE *table) {
    switch (expression.type) {
        case E_atomic:
            expression.contents.atomicExpression = transformATOMIC_EXPRESSION(expression.contents.atomicExpression, table);
            return expression;
        case E_unary:
            expression.contents.unaryExpression = transformUNARY_EXPRESSION(expression.contents.unaryExpression, table);
            return expression;
        case E_binary:
            expression.contents.binaryExpression = transformBINARY_EXPRESSION(expression.contents.binaryExpression, table);
            return expression;
        case E_ternary:
            expression.contents.ternaryExpression = transformTERNARY_EXPRESSION(expression.contents.ternaryExpression, table);
            return expression;
        default:
            return expression;
    }
}

BINARY_EXPRESSION transformBINARY_EXPRESSION(BINARY_EXPRESSION expression, SYMBOL_TABLE *table) {
    expression.lhs = transformATOMIC_EXPRESSION(expression.lhs, table);
    expression.rhs = transformATOMIC_EXPRESSION(expression.rhs, table);
    return expression;
}

UNARY_EXPRESSION transformUNARY_EXPRESSION(UNARY_EXPRESSION expression, SYMBOL_TABLE *table) {
    expression.operand = transformATOMIC_EXPRESSION(expression.operand, table);
}

TERNARY_EXPRESSION transformTERNARY_EXPRESSION(TERNARY_EXPRESSION expression, SYMBOL_TABLE *table) {

}

ATOMIC_EXPRESSION transformATOMIC_EXPRESSION(ATOMIC_EXPRESSION expression, SYMBOL_TABLE *table) {
    switch (expression.type) {
        case A_id:
            expression.contents.identifier.index = getIndex(table, expression.contents.identifier.id);
        case A_val:
        default:
            return expression;
    }
}