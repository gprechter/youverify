grammar SMTLibLisp;

expression: collection | atom;
collection: OPAREN (expressions+=expression)+ CPAREN;
atom: value=VALUE;

OPAREN      : '(' ;
CPAREN      : ')' ;
WHITESPACE	: ' ' -> skip ;

fragment CHAR_NO_NL : ~('\t'|'\\'|' '|'('|')');
VALUE: CHAR_NO_NL+ ;