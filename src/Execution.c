//
//  Execution.c
//  
//
//  Created by Griffin Prechter on 10/23/20.
//

#include "Execution.h"
#include "LinkedList.h"

VALUE evalAtom(ATOMIC_EXPRESSION expression, SYMBOL_TABLE *table) {
    switch (expression.type) {
        case A_id:
            return getVarByIndex(table, expression.contents.identifier.index);
        case A_val:
        default:
            return expression.contents.value;
    }
}

VALUE evalExpr(EXPRESSION expression, SYMBOL_TABLE *table) {
    switch (expression.type) {
        case E_atomic:
            return evalAtom(expression.contents.atomicExpression, table);
        case E_unary: {
            VALUE value = evalAtom(expression.contents.atomicExpression, table);
            VALUE unused;
            return (*apply[expression.contents.unaryExpression.op])(value, unused);
        }
        case E_binary: {
            VALUE lhs = evalAtom(expression.contents.binaryExpression.lhs, table);
            VALUE rhs = evalAtom(expression.contents.binaryExpression.rhs, table);
            return (*apply[expression.contents.binaryExpression.op])(lhs, rhs);
        }
        case E_ternary:
        default: {
            VALUE pred = evalAtom(expression.contents.ternaryExpression.first, table);
            VALUE then = evalAtom(expression.contents.ternaryExpression.second, table);
            VALUE el = evalAtom(expression.contents.ternaryExpression.third, table);
            if (pred.type == VALUE_TYPE_boolean && pred.contents.BOOLEAN) {
                return then;
            } else {
                return el;
            }
        }
    }
}

PC executeAssignment(PC pc, ASSIGNMENT_INSTRUCTION instruction, SYMBOL_TABLE *table) {
    setVarByIndex(table,
                  instruction.id.index,
                  evalExpr(instruction.expression, table)
                  );
    return pc + 1;
}

PC executeBranch(PC pc, GOTO_INSTRUCTION instruction, SYMBOL_TABLE *table) {
    VALUE pred = evalExpr(instruction.predicate, table);
    if (pred.type == VALUE_TYPE_boolean && pred.contents.BOOLEAN) {
        return table->destinations[instruction.destination.index];
    } else {
        return pc + 1;
    }
}

VALUE applyAND(VALUE lhs, VALUE rhs) {
    VALUE res;
    res.type = VALUE_TYPE_boolean;
    res.contents.BOOLEAN = lhs.contents.BOOLEAN && rhs.contents.BOOLEAN;
    return res;
}

VALUE applyOR(VALUE lhs, VALUE rhs) {
    VALUE res;
    res.type = VALUE_TYPE_boolean;
    res.contents.BOOLEAN = lhs.contents.BOOLEAN || rhs.contents.BOOLEAN;
    return res;
}

VALUE applyNOT(VALUE lhs, VALUE rhs) {
    VALUE res;
    res.type = VALUE_TYPE_boolean;
    res.contents.BOOLEAN = !lhs.contents.BOOLEAN;
    return res;
}

VALUE applyIMPLIES(VALUE lhs, VALUE rhs) {
    VALUE res;
    res.type = VALUE_TYPE_boolean;
    bool lhsVal = lhs.contents.BOOLEAN;
    bool rhsVal = rhs.contents.BOOLEAN;
    res.contents.BOOLEAN = !lhsVal || (lhsVal && rhsVal);
    return res;
}

VALUE applyXOR(VALUE lhs, VALUE rhs) {
    VALUE res;
    res.type = VALUE_TYPE_boolean;
    bool lhsVal = lhs.contents.BOOLEAN;
    bool rhsVal = rhs.contents.BOOLEAN;
    res.contents.BOOLEAN = lhsVal != rhsVal;
    return res;
}

VALUE applyEQUALS(VALUE lhs, VALUE rhs) {
    VALUE res;
    res.type = VALUE_TYPE_boolean;
    if (lhs.type == VALUE_TYPE_boolean && rhs.type == VALUE_TYPE_boolean) {
        bool lhsVal = lhs.contents.BOOLEAN;
        bool rhsVal = rhs.contents.BOOLEAN;
        res.contents.BOOLEAN = lhsVal == rhsVal;
    } else if (lhs.type == VALUE_TYPE_integer && rhs.type == VALUE_TYPE_integer) {
        int lhsVal = lhs.contents.INT;
        int rhsVal = rhs.contents.INT;
        res.contents.INT = lhsVal == rhsVal;
    }
    
    return res;
}

VALUE applyDISTINCT(VALUE lhs, VALUE rhs) {
    return applyXOR(lhs, rhs);
}

VALUE applyADD(VALUE lhs, VALUE rhs) {
    VALUE res;
    res.type = VALUE_TYPE_integer;
    int lhsVal = lhs.contents.INT;
    int rhsVal = rhs.contents.INT;
    res.contents.INT = lhsVal + rhsVal;
    return res;
}

VALUE applySUB(VALUE lhs, VALUE rhs) {
    VALUE res;
    res.type = VALUE_TYPE_integer;
    int lhsVal = lhs.contents.INT;
    int rhsVal = rhs.contents.INT;
    res.contents.INT = lhsVal - rhsVal;
    return res;
}

void initExecuteFunctions() {
    execute[0] = executeAssignment;
    execute[1] = executeBranch;
}

void initApplyFunctions() {
    apply[0] = applyAND;
    apply[1] = applyOR;
    apply[2] = applyNOT;
    apply[3] = applyIMPLIES;
    apply[4] = applyXOR;
    apply[5] = applyEQUALS;
    apply[6] = applyDISTINCT;
    apply[7] = applyADD;
    apply[8] = applySUB;

}
