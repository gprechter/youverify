%{
    #include <stdbool.h>
    #include "y.tab.h"
%}

%%
"&&"     {return AND;}
"||"     {return OR;}
"false"   {yylval.val = false; return BOOL;}
"true"  {yylval.val = true; return BOOL;}
\n      {return EOL;}
[ \t]   {}
.       {printf("unsupported");}
%%
