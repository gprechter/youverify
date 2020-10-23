%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include "Queue.h"
    #include "LinkedList.h"
    #include "LinkedList.c"
    #include "DoubleLink.h"
    #include "AST.h"
    #include "Execution.h"
    int yylex();
    int yyerror();
    QueuePtr instQueue;
    LinkedListPtr labels;
    int lineNumber = 0;
    extern FILE *yyin;
    
%}
%union {
    struct atom *val;
    struct atom *id;
    struct expression *e;
    struct inst *i;
    int num;
}
%token <val> BOOL INTEGER
%token <id> IDENTIFIER
%token <num> NUMBER
%token NOT IMPLIES AND OR XOR EQUALS DISTINCT
%token PLUS MINUS
%token QMARK COLON
%token ASSIGN IF GOTO
%token EOL
%type <e> expr
%type <val> term
%type <i> stmt
%type <i> stmtlabelized

%%
calclist:
| calclist stmtlabelized {
    printf("ADDING INSTRUCTION\n");
    push(instQueue, $2);
    lineNumber++;
}
| calclist stmtlabelized EOL {
    printf("ADDING INSTRUCTION\n");
    push(instQueue, $2);
    lineNumber++;
}

stmtlabelized: IDENTIFIER COLON stmt {
    printf("ADDING LABEL\n");
    struct label *l = malloc(sizeof(struct label));
    l->id = $1->c.id;
    l->dest = lineNumber;
    add(labels, l);
    $$ = $3;
}
| stmt

stmt: IDENTIFIER ASSIGN expr {
    struct inst* i = malloc(sizeof(struct inst));
    i->type = I_assignment;
    struct assign* a = malloc(sizeof(struct assign));
    a->id = $1;
    a->e = $3;
    i->n.a = a;
    $$ = i;
}
| IF expr GOTO IDENTIFIER {
    struct inst* i = malloc(sizeof(struct inst));
    i->type = I_branch;
    struct branch* b = malloc(sizeof(struct branch));
    b->e = $2;
    b->dest = $4;
    i->n.b = b;
    $$ = i;
}

expr: term {
    Expression *e = malloc(sizeof(Expression));
    e->type = E_atomic;
    e->e.a = $1;
    $$ = e;
}
| NOT term {
    Expression *e = malloc(sizeof(Expression));
    e->type = E_unary;
    struct unary *u = malloc(sizeof(struct unary));
    u->op = OP_not;
    u->val = $2;
    e->e.u = u;
    $$ = e;
}
| term AND term {
    Expression *e = malloc(sizeof(Expression));
    e->type = E_binary;
    struct binary *b = malloc(sizeof(struct binary));
    b->op = OP_and;
    b->lhs = $1;
    b->rhs = $3;
    e->e.b = b;
    $$ = e;
}
| term OR term {
    Expression *e = malloc(sizeof(Expression));
    e->type = E_binary;
    struct binary *b = malloc(sizeof(struct binary));
    b->op = OP_or;
    b->lhs = $1;
    b->rhs = $3;
    e->e.b = b;
    $$ = e;
}
| term IMPLIES term {
    Expression *e = malloc(sizeof(Expression));
    e->type = E_binary;
    struct binary *b = malloc(sizeof(struct binary));
    b->op = OP_implies;
    b->lhs = $1;
    b->rhs = $3;
    e->e.b = b;
    $$ = e;
}
| term XOR term {
    Expression *e = malloc(sizeof(Expression));
    e->type = E_binary;
    struct binary *b = malloc(sizeof(struct binary));
    b->op = OP_xor;
    b->lhs = $1;
    b->rhs = $3;
    e->e.b = b;
    $$ = e;
}
| term EQUALS term {
    Expression *e = malloc(sizeof(Expression));
    e->type = E_binary;
    struct binary *b = malloc(sizeof(struct binary));
    b->op = OP_equals;
    b->lhs = $1;
    b->rhs = $3;
    e->e.b = b;
    $$ = e;
}
| term DISTINCT term {
    Expression *e = malloc(sizeof(Expression));
    e->type = E_binary;
    struct binary *b = malloc(sizeof(struct binary));
    b->op = OP_distinct;
    b->lhs = $1;
    b->rhs = $3;
    e->e.b = b;
    $$ = e;
}
| term QMARK term COLON term {
    Expression *e = malloc(sizeof(Expression));
    e->type = E_ternary;
    struct ternary *t = malloc(sizeof(struct ternary));
    t->first = $1;
    t->second = $3;
    t->third = $5;
    e->e.t = t;
    $$ = e;
}
| term PLUS term {
    Expression *e = malloc(sizeof(Expression));
    e->type = E_binary;
    struct binary *b = malloc(sizeof(struct binary));
    b->op = OP_add;
    b->lhs = $1;
    b->rhs = $3;
    e->e.b = b;
    $$ = e;
}
| term MINUS term {
    Expression *e = malloc(sizeof(Expression));
    e->type = E_binary;
    struct binary *b = malloc(sizeof(struct binary));
    b->op = OP_subtract;
    b->lhs = $1;
    b->rhs = $3;
    e->e.b = b;
    $$ = e;
}
;

term: BOOL
| INTEGER
| IDENTIFIER
;
%%

yyerror(char *s) {
    fprintf(stderr, "error: %s\n", s);
}

void freeInst(void *ptr) {
    free((struct inst *) ptr);
}

FILE *readFile(char *filename) {
    FILE *fp;
    fp = fopen(filename,"r");
    return fp;
}

struct inst *getProgramArray(char *filename, int *prgmSize) {
    instQueue = newQueue();
    yyin = readFile(filename);
    yyparse();
    printf("decoding program\n");
    struct inst *prgmArr = (struct inst *) malloc(sizeof(struct inst) * instQueue->size);
    *prgmSize = instQueue->size;
    int i = 0;
    while(!isEmpty(instQueue)) {
        struct inst* inst = (struct inst*) pop(instQueue);
        prgmArr[i] = *inst;
        free(inst);
        i++;
    }
    freeQueue(instQueue, freeInst);
    return prgmArr;
}

main(int argc, char **argv) {
    instQueue = newQueue();
    labels = newLinkedList();
    int prgmSize;
    struct inst *prgmArr;
    if (argc > 1) {
        prgmArr = getProgramArray(argv[1], &prgmSize);
    }
    initExecuteFunctions();
    initApplyFunctions();
    int pc = 0;
    printf("Program Size: %d\n", prgmSize);
    LinkedListPtr regFile = newLinkedList();
    while (pc< prgmSize) {
        pc = (*execute[prgmArr[pc].type])(pc, prgmArr[pc], regFile, labels);
    }
    int i = 0;
    DoubleLinkPtr ptr = regFile->head;
    printf("\n\nREG COUNT: %d\n-------------------\n", regFile->size);
    while (i < regFile->size) {
        Value val = ((struct reg*)ptr->elem)->val;
        if (val.type == V_boolean) {
            printf("%s (bool): %s\n",((struct reg*)ptr->elem)->id, *((bool *)val.value) ? "true" : "false");
        } else {
            printf("%s (int): %d\n",((struct reg*)ptr->elem)->id, *((int *)val.value));
        }
        ptr = ptr->next;
        i++;
    }
    free(prgmArr);
}
