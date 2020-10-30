%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
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
    int lineNumber = 0;
    extern FILE *yyin;

    struct label {
        char *id;
        int dest;
    };
    
%}
%union {
    VALUE value;
    IDENTIFIER id;
    ATOMIC_EXPRESSION atom;
    EXPRESSION expression;
    INSTRUCTION instr;
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
%type <instr> stmt

%%
calclist:
| calclist stmt {
    printf("ADDING INSTRUCTION\n");
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = $2;
    push(instQueue, iPtr);
    lineNumber++;
}
| calclist stmt EOL {
    printf("ADDING INSTRUCTION\n");
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = $2;
    push(instQueue, iPtr);
    lineNumber++;
}

stmt: TOKEN_IDENTIFIER ASSIGN expr {
    $$ = newASSIGNMENT_INSTRUCTION($1, $3);
}
| IF expr GOTO TOKEN_IDENTIFIER {
    $$ = newGOTO_INSTRUCTION($2, $4);
}

expr: term {
    $$ = newATOMIC_EXPRESSION($1);
}


term: BOOL { $$ = newATOMIC_EXPRESSION_VALUE($1); }
| INTEGER { $$ = newATOMIC_EXPRESSION_VALUE($1); }
| TOKEN_IDENTIFIER { $$ = newATOMIC_EXPRESSION_IDENTIFIER($1); }

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
    //labels = newLinkedList();
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
    struct inst *prgmArr;
    if (argc > 1) {
        prgmArr = getProgramArray(argv[1], &prgmSize);
    }
    int pc = 0;
    printf("Program Size: %d\n", prgmSize);

    free(prgmArr);
}