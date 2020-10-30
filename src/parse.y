%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include "IdentifierLinkedList.h"
    #include "TypeChecker/TCInstruction.h"
    #include "Queue.h"
    #include "LinkedList.h"
    #include "DoubleLink.h"
    #include "AST/Value.h"
    #include "AST/Identifier.h"
    #include "AST/Expression.h"
    #include "AST/Instruction.h"
    #include "AST/Expressions/AtomicExpression.h"
    #include "Execution.h"

    int yylex();
    int yyerror();
    QueuePtr instQueue;
    LinkedListPtr labels;
    LinkedListPtr identifiers;
    int lineNumber = 0;
    extern FILE *yyin;

    typedef struct label {
        char *id;
        int dest;
    } LABEL;
    
%}
%union {
    VALUE value;
    IDENTIFIER id;
    ATOMIC_EXPRESSION atom;
    EXPRESSION expression;
    INSTRUCTION instr;
    VALUE_TYPE type;
    int num;
}
%token <value> BOOL INTEGER
%token <id> TOKEN_IDENTIFIER
%token <num> NUMBER
%token NOT IMPLIES AND OR XOR EQUALS DISTINCT
%token PLUS MINUS
%token QMARK COLON
%token ASSIGN IF GOTO
%token EOL
%type <expression> expr
%type <atom> term
%type <instr> line stmt
%token <type> TYPE
%%
calclist:
| calclist line {
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = $2;
    push(instQueue, iPtr);
    lineNumber++;
}
| calclist line EOL {
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = $2;
    push(instQueue, iPtr);
    lineNumber++;
}

line:
TOKEN_IDENTIFIER COLON stmt {
    LABEL *l = malloc(sizeof(LABEL));
    l->id = $1.id;
    l->dest = lineNumber;
    add(labels, l);
    $$ = $3;
}
| stmt

stmt: TOKEN_IDENTIFIER ASSIGN expr {
    $1.type = getTypeForIDENTIFIER(identifiers, $1);
    $$ = newASSIGNMENT_INSTRUCTION($1, $3);
}
| IF expr GOTO TOKEN_IDENTIFIER {
    $$ = newGOTO_INSTRUCTION($2, $4);
}
| TOKEN_IDENTIFIER COLON TYPE {
    IDENTIFIER *id = (IDENTIFIER *) malloc(sizeof(IDENTIFIER));
    *id = $1;
    id->type = $3;
    add(identifiers, id);
    $$ = newDECLARATION_INSTRUCTION($1, $3);
}

expr: term {
    $$ = newATOMIC_EXPRESSION($1);
}
| NOT term {
    $$ = newUNARY_EXPRESSION(OP_not, $2);
}
| MINUS term {
    $$ = newUNARY_EXPRESSION(OP_subtract, $2);
}
| term AND term {
    $$ = newBINARY_EXPRESSION($1, OP_and, $3);
}
| term OR term {
    $$ = newBINARY_EXPRESSION($1, OP_or, $3);
}
| term XOR term {
    $$ = newBINARY_EXPRESSION($1, OP_xor, $3);
}
| term IMPLIES term {
    $$ = newBINARY_EXPRESSION($1, OP_implies, $3);
}
| term PLUS term {
    $$ = newBINARY_EXPRESSION($1, OP_add, $3);
}
| term MINUS term {
    $$ = newBINARY_EXPRESSION($1, OP_subtract, $3);
}
| term EQUALS term {
    $$ = newBINARY_EXPRESSION($1, OP_equals, $3);
}
| term DISTINCT term {
    $$ = newBINARY_EXPRESSION($1, OP_distinct, $3);
}


term: BOOL { $$ = newATOMIC_EXPRESSION_VALUE($1); }
| INTEGER { $$ = newATOMIC_EXPRESSION_VALUE($1); }
| TOKEN_IDENTIFIER {
printf("Retreiving Identifier");
$1.type = getTypeForIDENTIFIER(identifiers, $1);
$$ = newATOMIC_EXPRESSION_IDENTIFIER($1);
}

%%

yyerror(char *s) {
    fprintf(stderr, "error: %s\n", s);
}

FILE *readFile(char *filename) {
    FILE *fp;
    fp = fopen(filename,"r");
    return fp;
}

struct inst *getProgramArray(char *filename, int *prgmSize) {
    instQueue = newQueue();
    labels = newLinkedList();
    identifiers = newLinkedList();
    yyin = readFile(filename);
    yyparse();
    printf("decoding program\n");
    INSTRUCTION *prgmArr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION) * instQueue->size);
    *prgmSize = instQueue->size;
    int i = 0;
    while(!isEmpty(instQueue)) {
        INSTRUCTION* inst = (INSTRUCTION*) pop(instQueue);
        printf("%d\n", inst->type);
        prgmArr[i] = *inst;
        free(inst);
        i++;
    }
    //freeQueue(instQueue, freeInst);

    return prgmArr;
}

main(int argc, char **argv) {
    instQueue = newQueue();
    int prgmSize;
    INSTRUCTION *prgmArr;
    if (argc > 1) {
        prgmArr = getProgramArray(argv[1], &prgmSize);
    }
    int pc = 0;
    printf("Program Size: %d\n", prgmSize);
    printf("Number of identifiers: %d\n", identifiers->size);

    for (pc = 0; pc < prgmSize; pc++) {
        printf("INSTRUCTION %d: %s\n", pc, checkINSTRUCTION(prgmArr[pc]) ? "true" : "false");
    }

    free(prgmArr);
}