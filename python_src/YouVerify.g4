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
stmt: 'return' expression=expr # RETURN
    | 'return' # RETURN_NO_VALUE
    | 'assume' expression=expr # ASSERT
    | target=assign_target '=' expression=expr # ASSIGN
    | 'call' target=assign_target '=' operator=IDENTIFIER OPAREN ((operands+=expr COMMA)* (operands+=expr)?) CPAREN #FUNC_CALL
    | 'call' operator=IDENTIFIER OPAREN ((operands+=expr COMMA)* (operands+=expr)?) CPAREN #FUNC_CALL_NO_VALUE
    | 'if' expression=expr 'goto' label=IDENTIFIER # CONDITIONAL_BRANCH
    | 'goto' label=IDENTIFIER # UNCONDITIONAL_BRANCH;
assign_target: identifier=IDENTIFIER # ASSIGN_TARGET_IDENTIFIER
             | rec=IDENTIFIER PERIOD item=IDENTIFIER # ASSIGN_TARGET_RECORD_INDEX
             | expression=array_index_expr # ASSIGN_TARGET_ARRAY_INDEX;
decl: ((identifiers+=IDENTIFIER COMMA)* (identifiers+=IDENTIFIER)?) ':' s=sort;
expr: (atom=BOOLEAN | atom=INTEGER | atom=IDENTIFIER) # ATOMIC
    | 'ARRAY[]' '{' expression=expr '}' # ARRAY
    | 'ARRAY[' length=INTEGER ']' '{' expression=expr '}' # FIXED_SIZE_ARRAY
    | 'BV' '{' value=INTEGER COMMA size=INTEGER '}' # BIT_VECTOR
    | '$sym' '{' s=sort '}' # SYMBOL
    | '$sym' '{' identifier=IDENTIFIER ',' s=sort '}' # NAMED_SYMBOL
    | rec=IDENTIFIER PERIOD item=IDENTIFIER # RECORD_INDEX
    | expression=array_index_expr # ARRAY_INDEX
    | op=OPERATOR e=expr # UNARY
    | lhs=expr op=OPERATOR rhs=expr # BINARY
    | first=expr op=TERNARY_OPERATOR second=expr COLON third=expr #TERNARY;
array_index_expr: array=IDENTIFIER '[' index=expr ']';
sort: (s='BOOL' | s='INT') | (s='ARRAY' '{' contained_sort=sort '}') | (s = 'BV' '[' size=INTEGER']') | s=IDENTIFIER;
BOOLEAN: 'true' | 'false';
OPERATOR: '&' | '|' | '^' | '=>' | '==' | '!='
| '+' | '-' | '*' | '/' | '%' | '<=' | '<' | '>=' | '>' | '!' | '@';
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