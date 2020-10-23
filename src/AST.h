//
//  AST.h
//
//
//  Created by Griffin Prechter on 10/8/20.
//

#ifndef AST_h
#define AST_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"

typedef struct inst Inst;
    typedef struct inst *InstPtr;
    
    enum exprtype {E_atomic, E_unary, E_binary, E_ternary};
    enum atomtype {A_id, A_val};

    enum valuetype {V_boolean, V_integer};

    typedef struct value {
        enum valuetype type;
        void *value;
    } Value;

struct label {
    char *id;
    int dest;
};

struct reg {
    char *id;
    Value val;
};
    
    struct atom {
        enum atomtype type;
        union C {
            char* id;
            Value val;
        } c;
    };
    
    enum optype {OP_and, OP_or, OP_not, OP_implies, OP_xor, OP_equals, OP_distinct, OP_add, OP_subtract};
    
    struct binary {
        struct atom *lhs;
        enum optype op;
        struct atom *rhs;
    };

    struct unary {
        enum optype op;
        struct atom *val;
    };

    struct ternary {
        struct atom *first;
        struct atom *second;
        struct atom *third;
    };
    
    typedef struct expression {
        enum exprtype type;
        union E {
            struct atom *a;
            struct unary *u;
            struct binary *b;
            struct ternary *t;
        } e;
    } Expression;

typedef int PC;
    
enum instructiontype {I_assignment, I_branch};

struct assign {
    struct atom *id;
    Expression *e;
};

struct branch {
    Expression* e;
    struct atom *dest;
};

typedef struct inst {
    enum instructiontype type;
    union N {
        struct branch *b;
        struct assign *a;
    } n;
} Instruction;

#endif /* AST_h */
