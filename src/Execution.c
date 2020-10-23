//
//  Execution.c
//  
//
//  Created by Griffin Prechter on 10/23/20.
//

#include "Execution.h"
#include "LinkedList.h"

Value evalAtom(struct atom* a, LinkedListPtr regFile) {
    if (a->type == A_id) {
        return ((struct reg*)getWithID(regFile, a->c.id))->val;
    } else {
        return a->c.val;
    }
}

Value evalExpr(Expression* expr, LinkedListPtr regFile) {
    if (expr->type == E_atomic) {
        return evalAtom(expr->e.a, regFile);
    } else if (expr->type == E_unary) {
        Value val = evalAtom(expr->e.u->val, regFile);
        Value unused;
        return (*apply[expr->e.u->op])(val, unused);
    } else if (expr->type == E_binary) {
        Value lhs = evalAtom(expr->e.b->lhs, regFile);
        Value rhs = evalAtom(expr->e.b->rhs, regFile);
        return (*apply[expr->e.b->op])(lhs, rhs);
    } else {
        Value pred = evalAtom(expr->e.t->first, regFile);
        Value then = evalAtom(expr->e.t->second, regFile);
        Value el = evalAtom(expr->e.t->third, regFile);
        if (pred.type == V_boolean && *((bool *) pred.value)) {
            return then;
        } else {
            return el;
        }
    }
}

PC executeAssignment(PC pc, Instruction instruction, LinkedListPtr regFile, LinkedListPtr labels) {
    struct reg *existing = (struct reg *)getWithID(regFile, instruction.n.a->id->c.id);
    if (existing == NULL) {
        struct reg *r = malloc(sizeof(struct reg));
        r->id = instruction.n.a->id->c.id;
        r->val = evalExpr(instruction.n.a->e, regFile);
        add(regFile, r);
    } else {
        existing->val = evalExpr(instruction.n.a->e, regFile);
    }
    return pc + 1;
}

PC executeBranch(PC pc, Instruction instruction, LinkedListPtr regFile, LinkedListPtr labels) {
    Value pred = evalExpr(instruction.n.b->e, regFile);
    if (pred.type == V_boolean && *((bool *) pred.value)) {
        return ((struct label *)getWithID(labels, instruction.n.b->dest->c.id))->dest;
    } else {
        return pc + 1;
    }
}

Value applyAND(Value lhs, Value rhs) {
    Value res;
    res.type = V_boolean;
    res.value = malloc(sizeof(bool));
    *((bool *)res.value) = *((bool *)lhs.value) && *((bool *)rhs.value);
    return res;
}

Value applyOR(Value lhs, Value rhs) {
    Value res;
    res.type = V_boolean;
    res.value = malloc(sizeof(bool));
    *((bool *)res.value) = *((bool *)lhs.value) || *((bool *)rhs.value);
    return res;
}

Value applyNOT(Value lhs, Value rhs) {
    Value res;
    res.type = V_boolean;
    res.value = malloc(sizeof(bool));
    *((bool *)res.value) = !(*((bool *)lhs.value));
    return res;
}

Value applyIMPLIES(Value lhs, Value rhs) {
    Value res;
    res.type = V_boolean;
    res.value = malloc(sizeof(bool));
    bool lhsVal = *((bool *)lhs.value);
    bool rhsVal = *((bool *)rhs.value);
    *((bool *)res.value) = !lhsVal || (lhsVal && rhsVal);
    return res;
}

Value applyXOR(Value lhs, Value rhs) {
    Value res;
    res.type = V_boolean;
    res.value = malloc(sizeof(bool));
    bool lhsVal = *((bool *)lhs.value);
    bool rhsVal = *((bool *)rhs.value);
    *((bool *)res.value) = lhsVal != rhsVal;
    return res;
}

Value applyEQUALS(Value lhs, Value rhs) {
    Value res;
    res.type = V_boolean;
    res.value = malloc(sizeof(bool));
    if (lhs.type == V_boolean && rhs.type == V_boolean) {
        bool lhsVal = *((bool *)lhs.value);
        bool rhsVal = *((bool *)rhs.value);
        *((bool *)res.value) = lhsVal == rhsVal;
    } else if (lhs.type == V_integer && rhs.type == V_integer) {
        int lhsVal = *((int *)lhs.value);
        int rhsVal = *((int *)rhs.value);
        *((bool *)res.value) = lhsVal == rhsVal;
    }
    
    return res;
}

Value applyDISTINCT(Value lhs, Value rhs) {
    return applyXOR(lhs, rhs);
}

Value applyADD(Value lhs, Value rhs) {
    Value res;
    res.type = V_integer;
    res.value = malloc(sizeof(int));
    int lhsVal = *((int *)lhs.value);
    int rhsVal = *((int *)rhs.value);
    *((int *)res.value) = lhsVal + rhsVal;
    return res;
}

Value applySUB(Value lhs, Value rhs) {
    Value res;
    res.type = V_integer;
    res.value = malloc(sizeof(int));
    int lhsVal = *((int *)lhs.value);
    int rhsVal = *((int *)rhs.value);
    *((int *)res.value) = lhsVal - rhsVal;
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
