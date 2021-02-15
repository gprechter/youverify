//
// Created by Griffin Prechter on 2/15/21.
//

#ifndef YOUVERIFY_PARSE_H
#define YOUVERIFY_PARSE_H

#include "Queue.h"

typedef struct program {
    QueuePtr declarations;
    QueuePtr statements;
} PROGRAM;

PROGRAM *parseProgram(char *filename);
#endif //YOUVERIFY_PARSE_H
