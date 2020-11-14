//
// Created by Griffin Prechter on 11/13/20.
//

#ifndef YOUVERIFY_HASHMAP_H
#define YOUVERIFY_HASHMAP_H
#define NUMBER_OF_BUCKETS 10
typedef struct elem {
    char *str;
    int value;
    struct elem * next;
} ELEM;

typedef struct hashmap {
    int numBuckets;
    ELEM *buckets[NUMBER_OF_BUCKETS];
} HashMap;

HashMap *newHashMap();
void HM_put(HashMap *map, char *str, int val);
int HM_get(HashMap *map, char *str);
void freeHashMap(HashMap *map);
#endif //YOUVERIFY_HASHMAP_H
