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
    #include "Analyze/HashMap.h"
    #include "Analyze/SymbolTable.h"
    #include "Analyze/Program.h"
    #include "Execution.h"

    int yylex();
    int yyerror();

    typedef struct program {
        QueuePtr declarations;
        QueuePtr statements;
    } PROGRAM;
    PROGRAM *RESULT;

    QueuePtr instQueue;
    LinkedListPtr functions;
    QueuePtr funcInstQueue;
    LinkedListPtr labels;
    LinkedListPtr identifiers;
    int lineNumber = 0;
    int funcLineNumber = 0;
    extern FILE *yyin;

    void freeElem_DO_NOTHING(void *elem) {

    }

    struct inst *getInstructionArray(QueuePtr instQueue, int *prgmSize) {
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

    typedef struct label {
        char *id;
        int dest;
    } LABEL;
    
%}
%union {
    VALUE value;
    Identifier id;
    ATOMIC_EXPRESSION atom;
    EXPRESSION expression;
    INSTRUCTION instr;
    VALUE_TYPE type;
    int num;
    struct queue *q;
}
%token <value> BOOL INTEGER
%token <id> IDENTIFIER
%token <num> NUMBER
%token NOT IMPLIES AND OR XOR EQUALS DISTINCT
%token PLUS MINUS
%token QMARK COLON OPAREN CPAREN COMMA
%token ASSIGN IF GOTO LAB DEFINE
%token BEGIN_FUNC END_FUNC ARROW
%token EOL
%type <expression> expr
%type <atom> term
%type <instr> stmt_with_opt_label stmt
%token <type> TYPE
%type <q> declarationandfunctionlist declarationlist stmtlist
%type <instr> declaration function
%%

program: declarationandfunctionlist stmtlist {
    PROGRAM *result = (PROGRAM *) malloc(sizeof(PROGRAM));
    result->declarations = $1;
    result->statements = $2;
    RESULT = result;
}

declarationandfunctionlist: {
   $$ = newQueue();
}
| declarationandfunctionlist function EOL {
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = $2;
    push($1, iPtr);
    $$ = $1;
}
| declarationandfunctionlist declaration EOL {
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = $2;
    push($1, iPtr);
    $$ = $1;
}

declarationlist: {
   $$ = newQueue();
}
| declarationlist declaration EOL {
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = $2;
    push($1, iPtr);
    $$ = $1;
}

function: DEFINE IDENTIFIER OPAREN CPAREN ARROW TYPE COLON EOL declarationlist stmtlist END_FUNC {
    $$ = newFUNCTION_DEFINE_INSTRUCTION($2, $6, $9, $10);
}

declaration: IDENTIFIER COLON TYPE {
    $$ = newDECLARATION_INSTRUCTION($1, $3);
}

stmtlist:
stmt_with_opt_label EOL {
    QueuePtr queue = newQueue();
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = $1;
    push(queue, iPtr);
    $$ = queue;
}
| stmtlist stmt_with_opt_label EOL {
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = $2;
    push($1, iPtr);
    $$ = $1;
}

stmt_with_opt_label:
LAB IDENTIFIER COLON stmt {
    $4.label = $2.id;
    $$ = $4;
}
| stmt

stmt: IDENTIFIER ASSIGN expr {
    $$ = newASSIGNMENT_INSTRUCTION($1, $3);
}
| IF expr GOTO IDENTIFIER {
    $$ = newGOTO_INSTRUCTION($2, $4);
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
| IDENTIFIER { $$ = newATOMIC_EXPRESSION_IDENTIFIER($1); }

%%

yyerror(char *s) {
    fprintf(stderr, "error: %s\n", s);
}

FILE *readFile(char *filename) {
    FILE *fp;
    fp = fopen(filename,"r");
    return fp;
}

PROGRAM *parseProgram(char *filename) {
    yyin = readFile(filename);
    yyparse();
    return RESULT;
}

main(int argc, char **argv) {
    PROGRAM *prgm;

    if (argc > 1) {
        prgm = parseProgram(argv[1]);
    }
    printf("Number of Declarations: %d \n", prgm->declarations->size);
    printf("Number of Statements: %d \n", prgm->statements->size);
    int num;
    SYMBOL_TABLE *table = createSymbolTable(prgm->declarations);
    int prgmSize;
    INSTRUCTION *checkedProgram = generateAndCheckProgramArray(prgm->statements, table, &prgmSize);
    int pc = 0;
    initApplyFunctions();
    while(pc < prgmSize) {
        if (checkedProgram[pc].type == I_assignment) {
            pc = executeAssignment(pc, checkedProgram[pc].contents.assignmentInstruction, table);
        } else {
            pc = executeBranch(pc, checkedProgram[pc].contents.gotoInstruction, table);
        }
    }
    printf("n: %d\n", getVar(table, "n").contents.INT);
    printf("result: %d\n", getVar(table, "result").contents.INT);
    printf("done: %s\n", getVar(table, "done").contents.BOOLEAN ? "true" : "false");
    //freeSymbolTable(table);
}