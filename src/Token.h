//
//  Token.h
//  
//
//  Created by Griffin Prechter on 10/8/20.
//

#ifndef Token_h
#define Token_h

#include <stdio.h>
#include <stdlib.h>

enum tokentype {TTnewline, TTidentifier, TTassign, TTop, TTnumber, TToparen, TTcparen};

typedef struct token Token;
typedef struct token *TokenPtr;
typedef enum tokentype TokenType;

struct token {
    TokenType type;
    char *string;
};

TokenPtr newToken(TokenType type, char *string);
void freeToken(TokenPtr token);
#endif /* Token_h */
