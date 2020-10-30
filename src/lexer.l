%{
    #include <stdbool.h>
    #include <string.h>
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
[a-zA-Z]+ {
    char *id = (char *) malloc(yyleng + 1);
    strcpy (id, yytext);
    IDENTIFIER identifier = newIDENTIFIER(id, VALUE_TYPE_unknown);
    return TOKEN_IDENTIFIER;
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
