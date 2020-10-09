//
//  Main.c
//  
//
//  Created by Griffin Prechter on 10/9/20.
//

#include <stdio.h>
#include "lex.yy.h"
#include "Queue.h"
#include "Token.h"

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    int count;
    TokenPtr tokens = lexer(argv[1], &count);
    printf("Number of Tokens: %d\n", count);
    int i;
    for(i = 0; i < count; i++) {
        printf("Type: %d -- \"%s\"\n", tokens[i].type, tokens[i].string);
        free(tokens[i].string);
    }
    free(tokens);
    
    return 0;
}
