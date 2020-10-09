/*** Definition Section has one variable 
which can be accessed inside yylex()  
and main() ***/
%{ 
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
#include "Token.h"

QueuePtr tokens;
%}
/*** Rule Section has three rules, first rule  
matches with capital letters, second rule 
matches with any character except newline and  
third rule does not take input after the enter***/
%%
[a-zA-Z_][a-zA-Z0-9_]*  {
    char *token = (char *) malloc(yyleng + 1);
    strcpy (token, yytext);
    TokenPtr tok = newToken(TTidentifier, token);
    push(tokens, tok);
}
0|[0-9][0-9]* {
	char *token = (char *) malloc(yyleng + 1);
	strcpy (token, yytext);
	TokenPtr tok = newToken(TTnumber, token);
	push(tokens, tok);
}
:= {
    char *token = (char *) malloc(yyleng + 1);
    strcpy (token, yytext);
    TokenPtr tok = newToken(TTassign, token);
    push(tokens, tok);
}
[\+|\-|\*|/]   {
    char *token = (char *) malloc(yyleng + 1);
    strcpy (token, yytext);
    TokenPtr tok = newToken(TTop, token);
    push(tokens, tok);
}
\n    {
    char *token = (char *) malloc(yyleng + 1);
    strcpy (token, yytext);
    TokenPtr tok = newToken(TTnewline, token);
    push(tokens, tok);
}

\( {
    char *token = (char *) malloc(yyleng + 1);
    strcpy (token, yytext);
    TokenPtr tok = newToken(TToparen, token);
    push(tokens, tok);
}

\) {
    char *token = (char *) malloc(yyleng + 1);
    strcpy (token, yytext);
    TokenPtr tok = newToken(TTcparen, token);
    push(tokens, tok);
}

<<EOF>> {
    yyterminate();
}

%% 
  
/*** Code Section prints the number of 
capital letter present in the given input***/
int yywrap(){}
/*
char filename[50];
printf("Enter the filename: \n");
scanf("%s",filename);
*/

FILE *readFile(char *filename) {
    FILE *fp;
    fp = fopen(filename,"r");
    return fp;
}

TokenPtr lexer(char *filename, int *count){ 
  
// Explanation: 
// yywrap() - wraps the above rule section 
/* yyin - takes the file pointer  
          which contains the input*/
/* yylex() - this is the main flex function 
          which runs the Rule Section*/
// yytext is the text in the buffer 
  
// Uncomment the lines below  
// to take input from file
	yyin = readFile(filename);
    tokens = newQueue();
    yylex();
    *count = tokens->size;
    TokenPtr tokensArr = (Token *) malloc(sizeof(Token) * tokens->size);
    
    int i = 0;
    while(!isEmpty(tokens)) {
        TokenPtr token = (TokenPtr) pop(tokens);
        tokensArr[i] = *token;
        free(token);
        i++;
    }
    freeQueue(tokens); 
    return tokensArr; 
} 
