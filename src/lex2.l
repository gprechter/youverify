%{
    #include <stdbool.h>
    #include <string.h>
    #include "y.tab.h"
    #include "AST.h"
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
    struct atom *a = (struct atom *) malloc(sizeof(struct atom));
    a->type = A_val;
    Value v;
    v.type = V_boolean;
    bool *b = (bool *) malloc(sizeof(bool));
    *b = false;
    v.value = b;
    a->c.val = v;
    yylval.val = a;
    return BOOL;}
"true"  {
    struct atom *a = (struct atom *) malloc(sizeof(struct atom));
    a->type = A_val;
    Value v;
    v.type = V_boolean;
    bool *b = (bool *) malloc(sizeof(bool));
    *b = true;
    v.value = b;
    a->c.val = v;
    yylval.val = a;
    return BOOL;
}
"="     {return ASSIGN;}
"if"    {return IF;}
"goto"  {return GOTO;}
[a-zA-Z]+ {
    char *id = (char *) malloc(yyleng + 1);
    strcpy (id, yytext);
    struct atom *a = (struct atom *) malloc(sizeof(struct atom));
    a->type = A_id;
    a->c.id = id;
    yylval.val = a;
    return IDENTIFIER;
}
"<"[0]|([1-9][0-9]+)">" {
    yylval.num = atoi(yytext);
    return NUMBER;
}
0|[1-9][0-9]* {
    struct atom *a = (struct atom *) malloc(sizeof(struct atom));
    a->type = A_val;
    Value v;
    v.type = V_integer;
    int *i = (int *) malloc(sizeof(int));
    *i = atoi(yytext);
    v.value = i;
    a->c.val = v;
    yylval.val = a;
    return INTEGER;
}
"?"	{return QMARK;}
":"	{return COLON;}
\n      {return EOL;}
[ \t]   {}
.       {printf("unsupported");}
%%
