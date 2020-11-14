//
// Created by Griffin Prechter on 11/13/20.
//

#include "HashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
    for (int i = 0; i < NUMBER_OF_BUCKETS; i++) {
        hashMap->buckets[i] = NULL;
    }
    return hashMap;
}

void HM_put(HashMap *map, char *str, int val) {
    int i = hash(str) % map->numBuckets;
    ELEM *bucket = map->buckets[i];
    ELEM *newElem = (ELEM *) malloc(sizeof(ELEM));
    newElem->str = str;
    newElem->value = val;
    newElem->next = bucket;
    map->buckets[i] = newElem;
}

int HM_get(HashMap *map, char *str) {
    int i = hash(str) % map->numBuckets;
    ELEM *bucket = map->buckets[i];
    while (bucket != NULL) {
        if (strcmp(str, bucket->str) == 0) {
            return bucket->value;
        }
        bucket = bucket->next;
    }
    return -1;
}

void freeElem(ELEM *elem) {
    if (elem != NULL) {
        freeElem(elem->next);
        free(elem->str);
        free(elem);
    }
}

void freeHashMap(HashMap *map) {
    for(int i = 0; i < map->numBuckets; i++) {
        freeElem(map->buckets[i]);
    }
    free(map);
}