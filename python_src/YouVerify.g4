grammar YouVerify;

program: ((decls+=global_decl NEWLINE)* (decls+=global_decl)?) ((stmts+=labeled_stmt NEWLINE)* (stmts+=labeled_stmt)?) EOF;
global_decl: var=decl       #GLOBAL_VAR
           | rec=record     #GLOBAL_REC
           | func=function  #GLOBAL_FUNC;
function: 'define' name=IDENTIFIER OPAREN ((params+=decl COMMA)* (params+=decl)?) CPAREN (ARROW return_type=sort)? COLON NEWLINE
                                                ((TAB decls+=decl NEWLINE)* (TAB decls+=decl)?)
                                                ((TAB stmts+=labeled_stmt NEWLINE)* (TAB stmts+=labeled_stmt)?);
record: 'record' name=IDENTIFIER OPAREN ((elems+=decl COMMA)* (elems+=decl)?) CPAREN;
labeled_stmt: 'LABEL' identifier=IDENTIFIER ':' statement=stmt # LABELED
            | statement=stmt # UNLABELED;
stmt: target=assign_target '=' expression=expr # ASSIGN
    | 'return' expression=expr # RETURN
    | 'return' # RETURN_NO_VALUE
    | 'assume' expression=expr # ASSUME
    | 'assert' expression=expr # ASSERT
    | 'call' target=assign_target '=' operator=IDENTIFIER OPAREN ((operands+=expr COMMA)* (operands+=expr)?) CPAREN #FUNC_CALL
    | 'call' operator=IDENTIFIER OPAREN ((operands+=expr COMMA)* (operands+=expr)?) CPAREN #FUNC_CALL_NO_VALUE
    | 'new' target=assign_target '=' operator=IDENTIFIER OPAREN ((operands+=expr COMMA)* (operands+=expr)?) CPAREN #ALLOC_CONC
    | 'new' target=assign_target '=' '$sym' '{' identifier=IDENTIFIER '}' # ALLOC_SYMB
    | 'if' expression=expr 'goto' label=IDENTIFIER # CONDITIONAL_BRANCH
    | 'goto' label=IDENTIFIER # UNCONDITIONAL_BRANCH;
assign_target: identifier=IDENTIFIER # ASSIGN_TARGET_IDENTIFIER
             | expression=record_index_expr # ASSIGN_TARGET_RECORD_INDEX
             | expression=array_index_expr # ASSIGN_TARGET_ARRAY_INDEX
             | expression=ptr_deref_expr # ASSIGN_TARGET_PTR_DEREF;
decl: ((identifiers+=IDENTIFIER COMMA)* (identifiers+=IDENTIFIER)?) ':' s=sort;
atomic_expr: (atom=BOOLEAN | atom=INTEGER | atom=IDENTIFIER) # SIMPLE
            | 'ARRAY[]' '{' expression=expr '}' # ARRAY
            | 'ARRAY[' length=INTEGER ']' '{' expression=expr '}' # FIXED_SIZE_ARRAY
            | 'BV' '{' value=INTEGER COMMA size=INTEGER '}' # BIT_VECTOR
            | '$sym' '{' s=sort '}' # SYMBOL
            | '$sym' '{' identifier=IDENTIFIER ',' s=sort '}' # NAMED_SYMBOL;
expr: atomic_expr
    | record_index_expr
    | array_index_expr
    | unary_expr
    | binary_expr
    | ternary_expr
    | ptr_deref_expr;
array_index_expr: array=IDENTIFIER '[' index=expr ']' # ARRAY_INDEX;
record_index_expr: rec=IDENTIFIER PERIOD item=IDENTIFIER # RECORD_INDEX;
unary_expr: op=OPERATOR e=atomic_expr # UNARY;
binary_expr: ((lhs=atomic_expr op=OPERATOR rhs=atomic_expr) | (lhs=atomic_expr op='*' rhs=atomic_expr)) # BINARY;
ptr_deref_expr: STAR identifier=IDENTIFIER;
ternary_expr: first=atomic_expr op=TERNARY_OPERATOR second=atomic_expr COLON third=atomic_expr #TERNARY;
sort: s=simple_sort '*' #PTR_SORT
    | s=simple_sort     #SIMPLE_SORT;
simple_sort: (s='BOOL' | s='INT') | (s='ARRAY' '{' contained_sort=sort '}') | (s = 'BV' '[' size=INTEGER']') | s=IDENTIFIER;
BOOLEAN: 'true' | 'false';
OPERATOR: '&' | '|' | '^' | '=>' | '==' | '!='
| '+' | '-' | '/' | '%' | '<=' | '<' | '>=' | '>' | '!' | '@';
STAR: '*';
TERNARY_OPERATOR: '?';
IDENTIFIER: [a-zA-Z]([a-zA-Z0-9]|'_')*;
INTEGER: '0'|([1-9][0-9]*);
NEWLINE		: ('\r'? '\n' | '\r')+ ;
ARROW       : '->';
COMMA       : ',' ;
OPAREN      : '(' ;
CPAREN      : ')' ;
COLON       : ':' ;
PERIOD      : '.' ;
TAB         : '\t' ;
WHITESPACE	: ' ' -> skip ;