//
//  Queue.h
//  
//
//  Created by Griffin Prechter on 10/8/20.
//

#ifndef Queue_h
#define Queue_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DoubleLink.h"

typedef struct queue Queue;
typedef struct queue *QueuePtr;

struct queue {
    int size;
    DoubleLinkPtr head;
    DoubleLinkPtr tail;
};

QueuePtr newQueue();
void push(QueuePtr queue, void *elem);
void *peek(QueuePtr queue);
void *pop(QueuePtr queue);
bool isEmpty(QueuePtr queue);
void freeQueue(QueuePtr queue);

#endif /* Queue_h */
