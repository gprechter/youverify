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

VALUE evalAtom(ATOMIC_EXPRESSION expression, SYMBOL_TABLE *table);

VALUE evalExpr(EXPRESSION expr, SYMBOL_TABLE *table);

PC executeAssignment(PC pc, ASSIGNMENT_INSTRUCTION instruction, SYMBOL_TABLE *table);

PC executeBranch(PC pc, GOTO_INSTRUCTION instruction, SYMBOL_TABLE *table);

PC (*execute[2])(PC pc, INSTRUCTION instruction, SYMBOL_TABLE *table);
VALUE (*apply[9])(VALUE lhs, VALUE rhs);

VALUE applyAND(VALUE lhs, VALUE rhs);
VALUE applyOR(VALUE lhs, VALUE rhs);
VALUE applyNOT(VALUE lhs, VALUE rhs);
VALUE applyIMPLIES(VALUE lhs, VALUE rhs);
VALUE applyXOR(VALUE lhs, VALUE rhs);
VALUE applyEQUALS(VALUE lhs, VALUE rhs);
VALUE applyDISTINCT(VALUE lhs, VALUE rhs);
VALUE applyADD(VALUE lhs, VALUE rhs);
VALUE applySUB(VALUE lhs, VALUE rhs);

void initExecuteFunctions();

void initApplyFunctions();

#endif /* Execution_h */
