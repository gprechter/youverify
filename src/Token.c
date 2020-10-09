//
//  Token.c
//  
//
//  Created by Griffin Prechter on 10/8/20.
//

#include "Token.h"

TokenPtr newToken(TokenType type, char *string) {
    TokenPtr token = (TokenPtr) malloc(sizeof(Token));
    token->type = type;
    token->string = string;
    return token;
}

void freeToken(TokenPtr token) {
    //if (token->string != NULL) free(token->string);
    free(token);
}
