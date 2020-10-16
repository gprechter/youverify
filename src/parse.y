%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "Queue.h"
    int yylex();
    int yyerror();
    QueuePtr instQueue;
    extern FILE *yyin;
%}
%union {
    _Bool val;
}
%token <val> BOOL
%token AND OR
%token EOL
%type <val> expr
%type <val> term

%%
calclist:
| calclist expr {
    bool *val = (bool *) malloc(sizeof(bool));
    *val = $2;
    push(instQueue, val);
}
| calclist expr EOL {
    bool *val = (bool *) malloc(sizeof(bool));
    *val = $2;
    push(instQueue, val);
}

expr: term
| expr AND term {$$ = $1 && $3;}
| expr OR term {$$ = $1 || $3;}
;

term: BOOL;
%%

yyerror(char *s) {
    fprintf(stderr, "error: %s\n", s);
}

void freeBool(void *ptr) {
    free((bool *) ptr);
}

FILE *readFile(char *filename) {
    FILE *fp;
    fp = fopen(filename,"r");
    return fp;
}

bool *getProgramArray(char *filename, int *prgmSize) {
    instQueue = newQueue();
    yyin = readFile(filename);
    yyparse();
    
    bool *prgmArr = (bool *) malloc(sizeof(bool) * instQueue->size);
    *prgmSize = instQueue->size;
    int i = 0;
    while(!isEmpty(instQueue)) {
        bool* inst = (bool *) pop(instQueue);
        prgmArr[i] = *inst;
        free(inst);
        i++;
    }
    freeQueue(instQueue, freeBool);
    return prgmArr;
}

main(int argc, char **argv) {
    instQueue = newQueue();
    int prgmSize;
    bool *prgmArr;
    if (argc > 1) {
        prgmArr = getProgramArray(argv[1], &prgmSize);
    }
    int i = 0;
    while (i < prgmSize) {
        printf("%s\n", prgmArr[i] ? "true" : "false");
        i++;
    }
    free(prgmArr);
}
