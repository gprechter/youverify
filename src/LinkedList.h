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
typedef LinkedListPtr List;


struct linkedlist {
    int size;
    DoubleLinkPtr head;
    DoubleLinkPtr tail;
};

LinkedListPtr newLinkedList();
void addFirst(LinkedListPtr lnk, void *elem);
void addLast(LinkedListPtr lnk, void *elem);
void *removeFirst(LinkedListPtr lnk);
void *removeLast(LinkedListPtr lnk);
void *get(LinkedListPtr lnk, bool(*cond)(void *elem));
LinkedListPtr concat(LinkedListPtr a, LinkedListPtr b);
bool isEmptyLL(LinkedListPtr lnk);
void freeLinkedList(LinkedListPtr lnk, void (*freeElem)(void*));

#endif /* LinkedList_h */
