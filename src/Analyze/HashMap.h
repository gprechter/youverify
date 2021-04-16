//
// Created by Griffin Prechter on 11/13/20.
//

#ifndef YOUVERIFY_HASHMAP_H
#define YOUVERIFY_HASHMAP_H

#include <stdbool.h>
#include "Queue.h"

#define NUMBER_OF_BUCKETS 10

typedef struct elem {
    void* id;
    void* data;
    struct elem * next;
} ELEM;

typedef struct hashmap {
    int numBuckets;
    int numElements;
    ELEM *buckets[NUMBER_OF_BUCKETS];
} HashMap;

HashMap *newHashMap();
void HM_put(HashMap *map, char *str, void* data);
bool HM_get(HashMap *map, char *str, void** data);
QueuePtr HM_getKeys(HashMap *map);
void freeHashMap(HashMap *map);
#endif //YOUVERIFY_HASHMAP_H
