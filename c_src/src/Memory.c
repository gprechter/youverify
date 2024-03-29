//
// Created by Griffin Prechter on 12/3/20.
//

#include "Memory.h"
#include <stdio.h>

void pushActivationFrame(int words, RuntimeEnvironment *environment) {
    // make room for all of the specified data + control link
    void *controlLink = environment->sp;
    environment->sp = environment->sp - ((words) * WORD_SIZE + LINK_SIZE);
    *((char **)environment->sp) = controlLink;
}

uint8_t* pushWord(uint8_t * sp) {
    return sp - WORD_SIZE;
}

uint8_t* popWord(uint8_t * sp) {
    return sp + WORD_SIZE;
}

void *getControlLink(RuntimeEnvironment *environment) {
    return (environment->sp);
}

void popActivationFrame(RuntimeEnvironment *environment) {
    environment->sp = *((char **)environment->sp);
}

void *getLocalVar(int n, RuntimeEnvironment *environment) {
    char * cntrlLink =  *((char **)getControlLink(environment));
    return (cntrlLink - (n) * WORD_SIZE);
}

RuntimeEnvironment *newRuntimeEnvironment(int size, SYMBOL_TABLE* symbolTable) {
    RuntimeEnvironment *newEnvironment = (RuntimeEnvironment *) malloc(sizeof(RuntimeEnvironment));
    newEnvironment->memory = malloc(size * WORD_SIZE);
    newEnvironment->sp = newEnvironment->memory + size * WORD_SIZE;
    newEnvironment->heap_base = newEnvironment->memory;
    newEnvironment->top = newEnvironment->sp;

    newEnvironment->sp = newEnvironment->sp - (symbolTable->totalRequiredBits / 32) * WORD_SIZE;

    DoubleLinkPtr curr = symbolTable->LocalArrayBindings->head;
    while (curr != NULL) {
        struct LocalArrayBindingInfo info = *( (struct LocalArrayBindingInfo *) curr->elem);
        newEnvironment->sp = newEnvironment->sp - (info.arrayMeta.elementType->bits / 8) * info.arrayMeta.elements;
        *((uint8_t **)getGlobalVar((info.variableIndex / 32 + 2), newEnvironment)) = newEnvironment->sp;
        curr = curr->next;
    }
    return newEnvironment;
}

void *getGlobalVar(int wordOffset, RuntimeEnvironment *environment) {
    return environment->top - (wordOffset) * WORD_SIZE;
}

uint8_t *allocate(int words, RuntimeEnvironment *environment) {
    uint8_t* allocated = environment->heap_base;
    environment->heap_base = environment->heap_base + words * WORD_SIZE;
    return allocated;
}