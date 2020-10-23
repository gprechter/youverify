//
//  LinkedList.c
//  
//
//  Created by Griffin Prechter on 10/15/20.
//

#include "LinkedList.h"
#include "AST.h"
#include <string.h>

LinkedListPtr newLinkedList() {
    LinkedListPtr lnk = (LinkedListPtr) malloc(sizeof(LinkedList));
    lnk->size = 0;
    lnk->head = NULL;
    lnk->tail = NULL;
    return lnk;
}
void add(LinkedListPtr lnk, void *elem) {
    DoubleLinkPtr newHead = newLink(elem);
    DoubleLinkPtr oldHead = lnk->head;
    newHead->next = oldHead;
    lnk->head = newHead;
    if (oldHead == NULL) {
        lnk->tail = newHead;
    } else {
        oldHead->prev = newHead;
    }
    lnk->size++;
}
void *get(LinkedListPtr lnk, bool(*cond)(void *elem)) {
    DoubleLinkPtr ptr = lnk->head;
    while (ptr != NULL) {
        if ((*cond)(ptr->elem)) return ptr->elem;
        ptr = ptr->next;
    }
    return NULL;
}

void *getWithID(LinkedListPtr lnk, char *id) {
    DoubleLinkPtr ptr = lnk->head;
    while (ptr != NULL) {
        if (!strcmp(((struct reg*)(ptr->elem))->id, id)) return ptr->elem;
        ptr = ptr->next;
    }
    return NULL;
}

bool isEmptyLL(LinkedListPtr lnk) {
    return lnk->size == 0;
}
void freeLinkedList(LinkedListPtr lnk, void (*freeElem)(void*)) {
    DoubleLinkPtr ptr = lnk->head;
    while (ptr != NULL) {
        DoubleLinkPtr tmp = ptr;
        ptr = ptr->next;
        (*freeElem)(ptr->elem);
        free(tmp);
    }
    free(lnk);
}
