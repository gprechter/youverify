//
//  LinkedList.c
//  
//
//  Created by Griffin Prechter on 10/15/20.
//

#include "LinkedList.h"
#include <string.h>

LinkedListPtr newLinkedList() {
    LinkedListPtr lnk = (LinkedListPtr) malloc(sizeof(LinkedList));
    lnk->size = 0;
    lnk->head = NULL;
    lnk->tail = NULL;
    return lnk;
}
void addFirst(LinkedListPtr lnk, void *elem) {
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

void addLast(LinkedListPtr lnk, void *elem) {
    DoubleLinkPtr newTail = newLink(elem);
    DoubleLinkPtr oldTail = lnk->tail;
    newTail->prev = oldTail;
    lnk->tail = newTail;
    if (oldTail == NULL) {
        lnk->head = newTail;
    } else {
        oldTail->next = newTail;
    }
    lnk->size++;
}

void *removeFirst(LinkedListPtr lnk) {
    if (lnk->head != NULL) {
        DoubleLinkPtr head = lnk->head;
        void* element = head->elem;
        lnk->head = head->next;
        if (lnk->head == NULL) {
            lnk->tail = NULL;
        } else {
            lnk->head->prev = NULL;
        }
        free(head);
        lnk->size--;
        return element;
    } else {
        return NULL;
    }
}

void *removeLast(LinkedListPtr lnk) {
    if (lnk->tail != NULL) {
        DoubleLinkPtr tail = lnk->tail;
        void* element = tail->elem;
        lnk->tail = tail->prev;
        if (lnk->tail == NULL) {
            lnk->head = NULL;
        } else {
            lnk->tail->next = NULL;
        }
        free(tail);
        lnk->size--;
        return element;
    } else {
        return NULL;
    }
}

void *get(LinkedListPtr lnk, bool(*cond)(void *elem)) {
    DoubleLinkPtr ptr = lnk->head;
    while (ptr != NULL) {
        if ((*cond)(ptr->elem)) return ptr->elem;
        ptr = ptr->next;
    }
    return NULL;
}

LinkedListPtr concat(LinkedListPtr a, LinkedListPtr b) {
    a->size = a->size + b->size;
    a->tail->next = b->head;
    if (b->head != NULL) {
        b->head->prev = a->tail;
    }
    if (b->tail != NULL) {
        a->tail = b->tail;
    }
    free(b);
    return a;
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
