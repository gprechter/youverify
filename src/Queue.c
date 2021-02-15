//
//  Queue.c
//  
//
//  Created by Griffin Prechter on 10/8/20.
//

#include "Queue.h"
#include "DoubleLink.h"

QueuePtr newQueue() {
    QueuePtr queue = (QueuePtr) malloc(sizeof(Queue));
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}
void push(QueuePtr queue, void *elem) {
    DoubleLinkPtr newHead = newLink(elem);
    DoubleLinkPtr oldHead = queue->head;
    newHead->next = oldHead;
    queue->head = newHead;
    if (oldHead == NULL) {
        queue->tail = newHead;
    } else {
        oldHead->prev = newHead;
    }
    queue->size++;
}
void *peek(QueuePtr queue) {
    if (isEmpty(queue)) return NULL;
    return queue->tail->elem;
}
void *pop(QueuePtr queue) {
    if (isEmpty(queue)) return NULL;
    void *elem = queue->tail->elem;
    DoubleLinkPtr newTail = queue->tail->prev;
    freeLink(queue->tail);
    queue->tail = newTail;
    queue->size--;
    return elem;
}

QueuePtr combineQueues(QueuePtr queue, QueuePtr other) {
    QueuePtr new = newQueue();
    while(!isEmpty(other)) {
        push(new, pop(other));
    }
    while(!isEmpty(queue)) {
        push(new, pop(queue));
    }
    return new;
}

bool isEmpty(QueuePtr queue) {
    return queue->size == 0;
}
void freeQueue(QueuePtr queue, void (*freeElem)(void*)) {
    while (!isEmpty(queue)) {
        (*freeElem)(pop(queue));
    }
    free(queue);
}
