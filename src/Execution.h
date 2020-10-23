//
//  Execution.h
//  
//
//  Created by Griffin Prechter on 10/23/20.
//

#ifndef Execution_h
#define Execution_h

#include <stdio.h>
#include "AST.h"
#include "LinkedList.h"

Value evalAtom(struct atom* a, LinkedListPtr regFile);

Value evalExpr(Expression* expr, LinkedListPtr regFile);

PC executeAssignment(PC pc, Instruction instruction, LinkedListPtr regFile, LinkedListPtr labels);

PC executeBranch(PC pc, Instruction instruction, LinkedListPtr regFile, LinkedListPtr labels);

PC (*execute[2])(PC pc, Instruction instruction, LinkedListPtr regFile, LinkedListPtr labels);
Value (*apply[9])(Value lhs, Value rhs);

Value applyAND(Value lhs, Value rhs);
Value applyOR(Value lhs, Value rhs);
Value applyNOT(Value lhs, Value rhs);
Value applyIMPLIES(Value lhs, Value rhs);
Value applyXOR(Value lhs, Value rhs);
Value applyEQUALS(Value lhs, Value rhs);
Value applyDISTINCT(Value lhs, Value rhs);
Value applyADD(Value lhs, Value rhs);
Value applySUB(Value lhs, Value rhs);

void initExecuteFunctions();

void initApplyFunctions();

#endif /* Execution_h */
