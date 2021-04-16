//
//  Execution.h
//  
//
//  Created by Griffin Prechter on 10/23/20.
//

#ifndef Execution_h
#define Execution_h

#include <stdio.h>

#include "Analyze/SymbolTable.h"
#include "Analyze/Function.h"
#include "Runtime/RT_Environment.h"
#include "Memory.h"

RT_Value evalAtom(RT_AtomicExpression expression, RT_Environment env);

RT_Value evalExpr(RT_Expression expr, RT_Environment env);

PC executeAssignment(PC pc, RT_AssignmentInstruction instruction, RT_Environment env);
RT_Value executeFunction(FUNCTION function, RT_Environment);
PC executeBranch(PC pc, RT_GotoInstruction instruction, RT_Environment env);

void assignVariable(RT_Environment env, int index, RT_Value value);

RT_Value retrieveVariable(RT_Environment env, int index);

void initExecuteFunctions();

void initApplyFunctions();

#endif /* Execution_h */
