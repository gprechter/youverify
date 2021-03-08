%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include "parse.h"
    #include "Queue.h"
    #include "LinkedList.h"
    #include "DoubleLink.h"
    #include "AST/Identifier.h"
    #include "AST/Expression.h"
    #include "AST/Instruction.h"
    #include "AST/Expressions/AtomicExpression.h"
    #include "Analyze/HashMap.h"
    #include "Analyze/SymbolTable.h"
    #include "Analyze/Program.h"
    #include "Execution.h"
    #include "Analyze/Function.h"

    int yylex();
    int yyerror();

    PROGRAM *RESULT;

    QueuePtr instQueue;
    LinkedListPtr functions;
    QueuePtr funcInstQueue;
    LinkedListPtr labels;
    LinkedListPtr identifiers;
    int lineNumber = 0;
    int funcLineNumber = 0;
    extern FILE *yyin;
    SYMBOL_TABLE attributes;
    
%}
%union {
    VALUE value;
    Identifier id;
    ATOMIC_EXPRESSION atom;
    EXPRESSION expression;
    INSTRUCTION instr;
    TYPE type;
    char* valueType;
    int num;
    QueuePtr q;
}
%token <value> BOOL INTEGER BITVECTOR REAL
%token <id> IDENTIFIER
%token <num> NUMBER
%token NOT IMPLIES AND OR XOR EQUALS DISTINCT DOT
%token PLUS MINUS
%token QMARK COLON OPAREN CPAREN COMMA OBRACKET CBRACKET OBRACE CBRACE
%token ASSIGN IF GOTO LAB DEFINE STRUCT ENDSTRUCT MEMALLOC
%token BEGIN_FUNC END_FUNC ARROW RETURN ASTERISK BITVEC
%token BV2NAT NAT2BV BVCONCAT BVEXTRACT BVNOT BVAND BVOR BVNEG BVADD BVMUL BVUDIV BVUREM BVSHL BVLSHR BVULT
%token RMINUS RADD RMUL RDIV RLEQ RLE RGEQ RGE
%token RITOREAL RITOINT RIISINT
%token EOL
%type <expression> expr
%type <atom> term
%type <instr> stmt_with_opt_label stmt
%type <type> T_TYPE R_TYPE
%token <valueType> C_TYPE
%type <q> declarations_and_functions declarations statements commalist exprlist identifier_list
%type <q> multiple_target_declaration
%type <instr> declaration function
%%

program: TYPE_DECLARATIONS declarations_and_functions statements {
    PROGRAM *result = (PROGRAM *) malloc(sizeof(PROGRAM));
    result->declarations = $2;
    result->statements = $3;
    RESULT = result;
}

TYPE_DECLARATIONS: TYPE_DECLARATIONS STRUCT IDENTIFIER OBRACE declarations CBRACE EOL {
  TYPE* newStructType = malloc(sizeof(TYPE));
  newStructType->id = getNextID();
  HashMap* fields = newHashMap();
  int totalSize = 0;
  while(!isEmpty($5)) {
    DECLARATION_INSTRUCTION decl = ((INSTRUCTION *) pop($5))->contents.declarationInstruction;
    FIELDINFO* field = malloc(sizeof(FIELDINFO));
    field->type = decl.type;
    field->offset = totalSize;
    totalSize = totalSize + decl.type.bits;
    HM_put(fields, decl.identifier.id, (void*)field);
  }
  newStructType->metadata.fields = fields;
  newStructType->bits = totalSize;
  HM_put(idToType, $3.id, (void*)newStructType);
}
| {}

declarations_and_functions: {
   $$ = newQueue();
}
| declarations_and_functions function EOL {
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = $2;
    push($1, iPtr);
    $$ = $1;
}
| declarations_and_functions multiple_target_declaration EOL {
    while(!isEmpty($2)) {
        push($1, pop($2));
    }
    $$ = $1;
}

declarations: {
   $$ = newQueue();
}
| declarations multiple_target_declaration EOL {
    while(!isEmpty($2)) {
        push($1, pop($2));
    }
    $$ = $1;
}

function: DEFINE IDENTIFIER OPAREN commalist CPAREN ARROW T_TYPE COLON EOL declarations statements END_FUNC {
    $$ = newFUNCTION_DEFINE_INSTRUCTION($2, $4, $7, $10, $11);
}

multiple_target_declaration: identifier_list COLON T_TYPE {
  QueuePtr queue = newQueue();
  while(!isEmpty($1)) {
      Identifier* idPtr = pop($1);
      INSTRUCTION* declarationInst = malloc(sizeof(INSTRUCTION));
      *declarationInst = newDECLARATION_INSTRUCTION(*idPtr, $3);
      free(idPtr);
      push(queue, (void *) declarationInst);
  }
  free($1);
  $$ = queue;
}


declaration: IDENTIFIER COLON T_TYPE {
    $$ = newDECLARATION_INSTRUCTION($1, $3);
}

R_TYPE: C_TYPE ASTERISK {
    TYPE type = getType("REF");
    TYPE* referencedType;
    HM_get(idToType, $1, &referencedType);
    type.metadata.referencedType = referencedType;
    $$ = type;
}
| R_TYPE ASTERISK {
    TYPE type = getType("REF");
    TYPE* referencedType = malloc(sizeof(TYPE));
    *referencedType = $1;
    type.metadata.referencedType = referencedType;
    $$ = type;
}

T_TYPE: C_TYPE { // TODO; make it so that Structures can be the type in an array
    TYPE* type;
    HM_get(idToType, $1, &type);
    $$ = *type;
}
| BITVEC INTEGER {
    TYPE type;
    type.id = TID_bitvector;
    type.bits = $2.contents.INT;
    $$ = type;
}
| R_TYPE {
    $$ = $1;
}
| OBRACKET C_TYPE CBRACKET {
   TYPE type = getType("ARR");
       TYPE* elemType = malloc(sizeof(TYPE));
       HM_get(idToType, $2, &elemType);
       type.metadata.array_info.elementType = elemType;
       type.metadata.array_info.elements = 0;
       $$ = type;
}
| OBRACKET C_TYPE COMMA INTEGER CBRACKET {
    TYPE type = getType("ARR");
    TYPE* elemType = malloc(sizeof(TYPE));
    HM_get(idToType, $2, &elemType);
    type.metadata.array_info.elementType = elemType;
    type.metadata.array_info.elements = $4.contents.INT;
    $$ = type;
}
| IDENTIFIER {
   TYPE type = getType($1.id);
   $$ = type;
}

identifier_list: IDENTIFIER {
     QueuePtr new = newQueue();
     Identifier *iPtr = (Identifier *) malloc(sizeof(Identifier));
     *iPtr = $1;
     push(new, (void *) iPtr);
     $$ = new;
}
| identifier_list COMMA IDENTIFIER {
  Identifier *iPtr = (Identifier *) malloc(sizeof(Identifier));
  *iPtr = $3;
  push($1, (void *) iPtr);
  $$ = $1;
}

commalist: {
  $$ = newQueue();
}
| declaration {
  QueuePtr new = newQueue();
  INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
  *iPtr = $1;
  push(new, iPtr);
  $$ = new;
}
| commalist COMMA declaration {
  INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
  *iPtr = $3;
  push($1, iPtr);
  $$ = $1;
}

statements:
stmt_with_opt_label EOL {
    QueuePtr queue = newQueue();
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = $1;
    push(queue, iPtr);
    $$ = queue;
}
| statements stmt_with_opt_label EOL {
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
    $$ = newASSIGNMENT_INSTRUCTION_TO_IDENTIFIER($1, $3);
}
| IDENTIFIER OBRACKET term CBRACKET ASSIGN expr {
    $$ = newASSIGNMENT_INSTRUCTION_TO_ARRAY_ELEM(newArrayAccessExpression($1, $3).contents.arrayAccessExpression, $6);
}
| IDENTIFIER DOT IDENTIFIER ASSIGN expr {
    $$ = newASSIGNMENT_INSTRUCTION_TO_FIELD(newFieldAccessExpression($1, $3).contents.fieldAccessExpression, $5);
}
| ASTERISK IDENTIFIER ASSIGN expr {
    $$ = newASSIGNMENT_INSTRUCTION_TO_REFERENCE(newDereferenceExpression($2).contents.dereferenceExpression, $4);
}
| IF expr GOTO IDENTIFIER {
    $$ = newGOTO_INSTRUCTION($2, $4);
}
| RETURN expr {
    $$ = newRETURN_INSTRUCTION($2);
}

exprlist: {
  $$ = newQueue();
}
| term {
  QueuePtr new = newQueue();
  EXPRESSION *ePtr = (EXPRESSION *) malloc(sizeof(EXPRESSION));
  *ePtr = newATOMIC_EXPRESSION($1);
  push(new, ePtr);
  $$ = new;
}
| exprlist COMMA term {
  EXPRESSION *ePtr = (EXPRESSION *) malloc(sizeof(EXPRESSION));
  *ePtr = newATOMIC_EXPRESSION($3);
  push($1, ePtr);
  $$ = $1;
}


expr: term {
    $$ = newATOMIC_EXPRESSION($1);
}
| NOT term {
    $$ = newUNARY_EXPRESSION(U_OP_NOT, $2);
}
| MINUS term {
    $$ = newUNARY_EXPRESSION(U_OP_MINUS, $2);
}
| '|' term {
    $$ = newUNARY_EXPRESSION(U_OP_ABS, $2);
}
| term AND term {
    $$ = newBINARY_EXPRESSION($1, B_OP_AND, $3);
}
| term OR term {
    $$ = newBINARY_EXPRESSION($1, B_OP_OR, $3);
}
| term XOR term {
    $$ = newBINARY_EXPRESSION($1, B_OP_XOR, $3);
}
| term IMPLIES term {
    $$ = newBINARY_EXPRESSION($1, B_OP_IMPLIES, $3);
}
| term PLUS term {
    $$ = newBINARY_EXPRESSION($1, B_OP_ADD, $3);
}
| term MINUS term {
    $$ = newBINARY_EXPRESSION($1, B_OP_SUB, $3);
}
| term ASTERISK term {
    $$ = newBINARY_EXPRESSION($1, B_OP_MUL, $3);
}
| term '/' term {
    $$ = newBINARY_EXPRESSION($1, B_OP_DIV, $3);
}
| term '%' term {
    $$ = newBINARY_EXPRESSION($1, B_OP_MOD, $3);
}
| term EQUALS term {
    $$ = newBINARY_EXPRESSION($1, B_OP_EQUALS, $3);
}
| term DISTINCT term {
    $$ = newBINARY_EXPRESSION($1, B_OP_DISTINCT, $3);
}
| BV2NAT term {
    $$ = newUNARY_EXPRESSION(U_BV2NAT, $2);
}
| NAT2BV term {
    $$ = newUNARY_EXPRESSION(U_NAT2BV, $2);
}
| term BVCONCAT term {
    $$ = newBINARY_EXPRESSION($1, B_BVCONCAT, $3);
}
| term RADD term {
    $$ = newBINARY_EXPRESSION($1, B_OP_RADD, $3);
}
| term RMINUS term {
    $$ = newBINARY_EXPRESSION($1, B_OP_RSUB, $3);
}
| term RMUL term {
    $$ = newBINARY_EXPRESSION($1, B_OP_RMUL, $3);
}
| term RDIV term {
    $$ = newBINARY_EXPRESSION($1, B_OP_RDIV, $3);
}
| term RLEQ term {
    $$ = newBINARY_EXPRESSION($1, B_OP_RLEQ, $3);
}
| term RLE term {
    $$ = newBINARY_EXPRESSION($1, B_OP_RLE, $3);
}
| term RGEQ term {
    $$ = newBINARY_EXPRESSION($1, B_OP_RGEQ, $3);
}
| term RGE term {
    $$ = newBINARY_EXPRESSION($1, B_OP_RGE, $3);
}
| term RMINUS term {
    $$ = newBINARY_EXPRESSION($1, B_OP_RSUB, $3);
}
| RMINUS term {
    $$ = newUNARY_EXPRESSION(U_OP_RMINUS, $2);
}
| term RADD term {
    $$ = newBINARY_EXPRESSION($1, B_OP_RADD, $3);
}
| BVEXTRACT term term term {
    $$ = newTERNARY_EXPRESSION(T_BVEXTRACT, $2, $3, $4);
}
| BVNOT term {
    $$ = newUNARY_EXPRESSION(U_BVNOT, $2);
}
| term BVAND term {
    $$ = newBINARY_EXPRESSION($1, B_BVAND, $3);
}
| term BVOR term {
    $$ = newBINARY_EXPRESSION($1, B_BVOR, $3);
}
| term BVSHL term {
    $$ = newBINARY_EXPRESSION($1, B_BVSHL, $3);
}
| term BVLSHR term {
    $$ = newBINARY_EXPRESSION($1, B_BVLSHR, $3);
}
| term BVULT term {
    $$ = newBINARY_EXPRESSION($1, B_BVULT, $3);
}
| BVNEG term {
    $$ = newUNARY_EXPRESSION(U_BVNEG, $2);
}
| term BVADD term {
    $$ = newBINARY_EXPRESSION($1, B_BVADD, $3);
}
| term BVMUL term {
    $$ = newBINARY_EXPRESSION($1, B_BVMUL, $3);
}
| term BVUDIV term {
    $$ = newBINARY_EXPRESSION($1, B_BVUDIV, $3);
}
| term BVUREM term {
    $$ = newBINARY_EXPRESSION($1, B_BVUREM, $3);
}
| RITOREAL term {
    $$ = newUNARY_EXPRESSION(U_OP_ITR, $2);
}
| RITOINT term {
    $$ = newUNARY_EXPRESSION(U_OP_RTI, $2);
}
| RIISINT term {
    $$ = newUNARY_EXPRESSION(U_OP_ISINT, $2);
}
| term QMARK term COLON term {
    $$ = newTERNARY_EXPRESSION(T_ITE, $1, $3, $5);
}
| IDENTIFIER OPAREN exprlist CPAREN {
    $$ = newFunctionCallExpression($1, $3);
}
| OBRACKET exprlist CBRACKET {
    $$ = newNewArrayExpression($2);
}
| IDENTIFIER OBRACKET term CBRACKET {
    $$ = newArrayAccessExpression($1, $3);
}
| IDENTIFIER DOT IDENTIFIER {
    $$ = newFieldAccessExpression($1, $3);
}
| MEMALLOC OPAREN INTEGER CPAREN {
    $$ = newMemoryAllocateExpression($3.contents.INT)
}
| ASTERISK IDENTIFIER {
    $$ = newDereferenceExpression($2);
}


term: BOOL { $$ = newATOMIC_EXPRESSION_VALUE($1); }
| INTEGER { $$ = newATOMIC_EXPRESSION_VALUE($1); }
| BITVECTOR { $$ = newATOMIC_EXPRESSION_VALUE($1); }
| REAL { $$ = newATOMIC_EXPRESSION_VALUE($1); }
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