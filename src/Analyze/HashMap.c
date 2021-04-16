//
// Created by Griffin Prechter on 11/13/20.
//

#include "HashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

HashMap *newHashMap() {
    HashMap *hashMap = malloc(sizeof(HashMap));
    hashMap->numBuckets = NUMBER_OF_BUCKETS;
    hashMap->numElements = 0;
    for (int i = 0; i < NUMBER_OF_BUCKETS; i++) {
        hashMap->buckets[i] = NULL;
    }
    return hashMap;
}

void HM_put(HashMap *map, char *str, void* data) {
    int i = hash(str) % map->numBuckets;
    ELEM *bucket = map->buckets[i];
    ELEM *newElem = (ELEM *) malloc(sizeof(ELEM));
    newElem->id = str;
    newElem->data = data;
    newElem->next = bucket;
    map->buckets[i] = newElem;
    map->numElements++;
}

bool HM_get(HashMap *map, char *str, void** data) {
    int i = hash(str) % map->numBuckets;
    ELEM *bucket = map->buckets[i];
    while (bucket != NULL) {
        if (strcmp(str, (char *) bucket->id) == 0) {
            *data = bucket->data;
            return true;
        }
        bucket = bucket->next;
    }
    return false;
}

void freeElem(ELEM *elem) {
    if (elem != NULL) {
        freeElem(elem->next);
        free(elem->id);
        free(elem);
    }
}

void freeHashMap(HashMap *map) {
    for(int i = 0; i < map->numBuckets; i++) {
        freeElem(map->buckets[i]);
    }
    free(map);
}

QueuePtr HM_getKeys(HashMap *map) {
    QueuePtr queue = newQueue();
    for (int i = 0; i < map->numBuckets; i++) {
        ELEM *bucket = map->buckets[i];
        while(bucket != NULL) {
            push(queue, bucket->id);
            bucket = bucket->next;
        }
    }
    return queue;
}