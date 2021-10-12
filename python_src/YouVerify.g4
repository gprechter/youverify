grammar YouVerify;

program: ((decls+=global_decl NEWLINE)* (decls+=global_decl)?) ((stmts+=labeled_stmt NEWLINE)* (stmts+=labeled_stmt)?) EOF;
global_decl: var=decl       #GLOBAL_VAR
           | rec=record     #GLOBAL_REC
           | func=function  #GLOBAL_FUNC;
function: 'define' name=IDENTIFIER OPAREN ((params+=decl COMMA)* (params+=decl)?) CPAREN COLON NEWLINE
                                                ((TAB decls+=decl NEWLINE)* (TAB decls+=decl)?)
                                                ((TAB stmts+=labeled_stmt NEWLINE)* (TAB stmts+=labeled_stmt)?);
record: 'record' name=IDENTIFIER OPAREN ((elems+=decl COMMA)* (elems+=decl)?) CPAREN;
labeled_stmt: 'LABEL' identifier=IDENTIFIER ':' statement=stmt # LABELED
            | statement=stmt # UNLABELED;
stmt: 'return' expression=expr # RETURN
    | target=assign_target '=' expression=expr # ASSIGN
    | 'call' target=assign_target '=' operator=IDENTIFIER OPAREN ((operands+=expr COMMA)* (operands+=expr)?) CPAREN #FUNC_CALL
    | 'if' expression=expr 'goto' label=IDENTIFIER # CONDITIONAL_BRANCH
    | 'goto' label=IDENTIFIER # UNCONDITIONAL_BRANCH;
assign_target: identifier=IDENTIFIER # ASSIGN_TARGET_IDENTIFIER
             | rec=IDENTIFIER PERIOD item=IDENTIFIER # ASSIGN_TARGET_RECORD_INDEX
             | expression=array_index_expr # ASSIGN_TARGET_ARRAY_INDEX;
decl: identifier=IDENTIFIER ':' s=sort;
expr: (atom=BOOLEAN | atom=INTEGER | atom=IDENTIFIER) # ATOMIC
    | 'ARRAY[]' '{' expression=expr '}' # ARRAY
    | 'BV' '{' value=INTEGER COMMA size=INTEGER '}' # BIT_VECTOR
    | '$sym' '{' s=sort '}' # SYMBOL
    | '$sym' '{' identifier=IDENTIFIER ',' s=sort '}' # NAMED_SYMBOL
    | rec=IDENTIFIER PERIOD item=IDENTIFIER # RECORD_INDEX
    | expression=array_index_expr # ARRAY_INDEX
    | op=UNARY_OPERATOR e=expr # UNARY
    | lhs=expr op=BINARY_OPERATOR rhs=expr # BINARY
    | op=TERNARY_OPERATOR first=expr second=expr third=expr #TERNARY;
array_index_expr: array=IDENTIFIER '[' index=expr ']';
sort: (s='BOOL' | s='INT') | (s='ARRAY' '[' contained_sort=sort ']') | (s = 'BV' '[' size=INTEGER']') | s=IDENTIFIER;
BOOLEAN: 'true' | 'false';
UNARY_OPERATOR: '!' | '@';
BINARY_OPERATOR: '&' | '|' | '+' | '-' | '*' | '/' | '%' | '<=' | '<' | '>=' | '>' | '==' | '!=';
TERNARY_OPERATOR: '?';
IDENTIFIER: [a-zA-Z]([a-zA-Z0-9]|'_')*;
INTEGER: '0'|([1-9][0-9]*);
NEWLINE		: ('\r'? '\n' | '\r')+ ;
COMMA       : ',' ;
OPAREN      : '(' ;
CPAREN      : ')' ;
COLON       : ':' ;
PERIOD      : '.' ;
TAB         : '\t' ;
WHITESPACE	: ' ' -> skip ;