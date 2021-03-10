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
#include "Memory.h"
#include "DSEState/DSEState.h"

SymbolicExpression evalAtom(RT_AtomicExpression expression, DSEState state);

SymbolicExpression evalExpr(RT_Expression expr, DSEState state);

DSEState executeAssignment(PC pc, RT_AssignmentInstruction instruction, DSEState state);
RT_Value executeFunction(FUNCTION function, RuntimeEnvironment *env);
DSEState* executeBranch(PC pc, RT_GotoInstruction instruction, DSEState state);

PC (*execute[2])(PC pc, RT_Instruction instruction, SYMBOL_TABLE *table);
RT_Value (*apply[9])(RT_Value lhs, RT_Value rhs);

RT_Value applyAND(RT_Value lhs, RT_Value rhs);
RT_Value applyOR(RT_Value lhs, RT_Value rhs);
RT_Value applyNOT(RT_Value lhs, RT_Value rhs);
RT_Value applyIMPLIES(RT_Value lhs, RT_Value rhs);
RT_Value applyXOR(RT_Value lhs, RT_Value rhs);
RT_Value applyEQUALS(RT_Value lhs, RT_Value rhs);
RT_Value applyDISTINCT(RT_Value lhs, RT_Value rhs);
RT_Value applyADD(RT_Value lhs, RT_Value rhs);
RT_Value applySUB(RT_Value lhs, RT_Value rhs);

void *getVarPointer(NAME_SCOPE scope, int n, RuntimeEnvironment *env);

RT_Value evaluateAsType(void *ptr, TYPE type);
void assignVariable(void *ptr, RT_Value value);

void initExecuteFunctions();

void initApplyFunctions();

#endif /* Execution_h */
