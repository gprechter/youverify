//
// Created by Griffin Prechter on 12/3/20.
//

#include <stdlib.h>
#include <stdint.h>

#ifndef YOUVERIFY_MEMORY_H
#define YOUVERIFY_MEMORY_H

#define WORD_SIZE 4
#define LINK_SIZE sizeof(uint8_t *)

#include "Analyze/Function.h"

typedef struct _RuntimeEnvironment RuntimeEnvironment;

struct _RuntimeEnvironment {
    uint8_t * memory;
    uint8_t * sp;
    uint8_t * top;
    uint8_t * heap_base;
    FUNCTION* functions;
};

RuntimeEnvironment *newRuntimeEnvironment(int size, SYMBOL_TABLE* symbolTable);

void *getControlLink(RuntimeEnvironment *environment);
void pushActivationFrame(int words, RuntimeEnvironment *environment);
uint8_t* pushWord(uint8_t* sp);
uint8_t* popWord(uint8_t* sp);
void popActivationFrame(RuntimeEnvironment *environment);

void *getLocalVar(int n, RuntimeEnvironment *environment);
void *getGlobalVar(int n, RuntimeEnvironment *environment);

uint8_t *allocate(int words, RuntimeEnvironment *environment);

#endif //YOUVERIFY_MEMORY_H
