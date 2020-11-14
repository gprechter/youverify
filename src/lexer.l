%{
    #include <stdbool.h>
    #include <string.h>
    #include "TypeChecker/TCInstruction.h"
    #include "AST/Value.h"
    #include "AST/Identifier.h"
    #include "AST/Expression.h"
    #include "AST/Instruction.h"
    #include "y.tab.h"
%}

%%
"&&"     {return AND;}
"||"     {return OR;}
"=>"	{return IMPLIES;}
"^^"	{return XOR;}
"=="	{return EQUALS;}
"!="	{return DISTINCT;}
"!"	{return NOT;}
"+"	{return PLUS;}
"-"	{return MINUS;}
"(" {return OPAREN;}
")" {return CPAREN;}
"," {return COMMA;}
"->" {return ARROW;}
"INT" {
    yylval.type = VALUE_TYPE_integer;
    return TYPE;
}
"BOOL" {
    yylval.type = VALUE_TYPE_boolean;
    return TYPE;
}
"false"   {
    VALUE value = newBooleanVALUE(false);
    yylval.value = value;
    return BOOL;
}
"true"  {
    VALUE value = newBooleanVALUE(true);
    yylval.value = value;
    return BOOL;
}
"="     {return ASSIGN;}
"if"    {return IF;}
"goto"  {return GOTO;}
"LABEL" {return LAB;}
"def"   {return DEFINE;}
"endef" {return END_FUNC;}

[a-zA-Z]+ {
    char *id = (char *) malloc(yyleng + 1);
    strcpy (id, yytext);
    yylval.id = newIDENTIFIER(id);
    return IDENTIFIER;
}
0|[1-9][0-9]* {
    VALUE value = newIntegerVALUE(atoi(yytext));
    yylval.value = value;
    return INTEGER;
}
"?"	{return QMARK;}
":"	{return COLON;}
\n      {return EOL;}
[ \t]   {}
.       {printf("unsupported");}
%%

int yywrap(){return 1;}
