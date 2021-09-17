grammar YouVerify;

program: ((decls+=decl NEWLINE)* (decls+=decl)?) ((stmts+=labeled_stmt NEWLINE)* (stmts+=labeled_stmt)?) EOF;
labeled_stmt: 'LABEL' identifier=IDENTIFIER ':' statement=stmt # LABELED
            | statement=stmt # UNLABELED;
stmt: target=assign_target '=' expression=expr # ASSIGN
    | 'if' expression=expr 'goto' label=IDENTIFIER # CONDITIONAL_BRANCH
    | 'goto' label=IDENTIFIER # UNCONDITIONAL_BRANCH;
assign_target: identifier=IDENTIFIER # ASSIGN_TARGET_IDENTIFIER
             | expression=array_index_expr # ASSIGN_TARGET_ARRAY_INDEX;
decl: identifier=IDENTIFIER ':' s=sort;
expr: (atom=BOOLEAN | atom=INTEGER | atom=IDENTIFIER) # ATOMIC
    | 'ARRAY[]' '{' expression=expr '}' # ARRAY
    | '$sym' '{' s=sort '}' # SYMBOL
    | '$sym' '{' identifier=IDENTIFIER ',' s=sort '}' # NAMED_SYMBOL
    | expression=array_index_expr # ARRAY_INDEX
    | lhs=expr op=OPERATOR rhs=expr # BINARY;
array_index_expr: array=IDENTIFIER '[' index=expr ']';
sort: (s='BOOL' | s='INT') | (s='ARRAY' '[' contained_sort=sort ']');
BOOLEAN: 'true' | 'false';
OPERATOR: '&' | '|' | '+' | '-' | '>=' | '<';
IDENTIFIER: [a-zA-Z]([a-zA-Z0-9]|'_')*;
INTEGER: ('0'|[1-9])[0-9]*;
NEWLINE		: ('\r'? '\n' | '\r')+ ;
WHITESPACE	: ' ' -> skip ;