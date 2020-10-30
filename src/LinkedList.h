//
//  LinkedList.h
//  
//
//  Created by Griffin Prechter on 10/15/20.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <stdio.h>
#include <stdbool.h>
#include "DoubleLink.h"

typedef struct linkedlist LinkedList;
typedef struct linkedlist *LinkedListPtr;

struct linkedlist {
    int size;
    DoubleLinkPtr head;
    DoubleLinkPtr tail;
};

LinkedListPtr newLinkedList();
void add(LinkedListPtr lnk, void *elem);
void *get(LinkedListPtr lnk, bool(*cond)(void *elem));
bool isEmptyLL(LinkedListPtr lnk);
void freeLinkedList(LinkedListPtr lnk, void (*freeElem)(void*));

#endif /* LinkedList_h */
