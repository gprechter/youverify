//
// Created by Griffin Prechter on 11/13/20.
//

#ifndef YOUVERIFY_PROGRAM_H
#define YOUVERIFY_PROGRAM_H
#include "AST/Instruction.h"
#include "Queue.h"
#include "Analyze/SymbolTable.h"
#include "Runtime/RT_Instruction.h"
RT_Instruction *generateProgramArray(QueuePtr instructions, SYMBOL_TABLE *table, int *programSize, NAME_SCOPE scope);
#endif //YOUVERIFY_PROGRAM_H
