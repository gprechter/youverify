//
// Created by Griffin Prechter on 10/30/20.
//

#ifndef YOUVERIFY_INSTRUCTION_H

#include <stdbool.h>
#include "TypeChecker/TCExpression.h"
#include "AST/Instruction.h"

bool checkINSTRUCTION(INSTRUCTION instruction, SYMBOL_TABLE *table);

bool checkGOTO_INSTRUCTION(GOTO_INSTRUCTION instruction, SYMBOL_TABLE *table);

bool checkASSIGNMENT_INSTRUCTION(ASSIGNMENT_INSTRUCTION instruction, SYMBOL_TABLE *table);

bool checkDECLARATION_INSTRUCTION(DECLARATION_INSTRUCTION instruction, SYMBOL_TABLE *table);

#endif //YOUVERIFY_INSTRUCTION_H
