//
// Created by Griffin Prechter on 10/30/20.
//

#ifndef YOUVERIFY_INSTRUCTION_H

#include <stdbool.h>
#include "AST/Instruction.h"

bool checkINSTRUCTION(INSTRUCTION instruction);

bool checkGOTO_INSTRUCTION(GOTO_INSTRUCTION instruction);

bool checkASSIGNMENT_INSTRUCTION(ASSIGNMENT_INSTRUCTION instruction);

bool checkDECLARATION_INSTRUCTION(DECLARATION_INSTRUCTION instruction);

#endif //YOUVERIFY_INSTRUCTION_H
