//
// Created by Griffin Prechter on 2/15/21.
//

#ifndef YOUVERIFY_PARSE_H
#define YOUVERIFY_PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Queue.h"
#include "LinkedList.h"
#include "DoubleLink.h"
#include "AST/Identifier.h"
#include "AST/Expression.h"
#include "AST/Instruction.h"
#include "AST/Expressions/AtomicExpression.h"
#include "Analyze/HashMap.h"
#include "Analyze/SymbolTable.h"
#include "Analyze/Program.h"
#include "Execution.h"
#include "Analyze/Function.h"

typedef struct program {
    QueuePtr declarations;
    QueuePtr statements;
} PROGRAM;

PROGRAM *parseProgram(char *filename);
#endif //YOUVERIFY_PARSE_H
