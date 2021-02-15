//
// Created by Griffin Prechter on 2/11/21.
//

#ifndef YOUVERIFY_LIST_H
#define YOUVERIFY_LIST_H
#define NUMBER_OF_BUCKETS

#include "LinkedList.h"

typedef struct _IntegerKeyHashMap{
    int numBuckets;
    int numElements;
    LinkedList *buckets[NUMBER_OF_BUCKETS];
} IntHashMap;

IntHashMap *newHashMap();
void IHM_put(IntHashMap *map, int str, void* value);
bool IHM_get(IntHashMap *map, int str, void** value);
void freeHashMap(IntHashMap *map);

#endif //YOUVERIFY_LIST_H
