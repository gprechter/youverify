//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_VALUE_H
#define YOUVERIFY_VALUE_H

#include <stdbool.h>
#include "stdint.h"
#include "Analyze/HashMap.h"


typedef enum _typeids {TID_boolean, TID_integer, TID_array, TID_reference, TID_real, TID_FP, TID_RoundngMode, TID_bitvector} TYPE_ID;

typedef enum _RoundingMode {RNE, RNA, RTP, RTN, RTZ} RoundingMode;

static int TYPE_ID_boolean = TID_boolean;
static uint32_t TYPE_SIZE_boolean = 32;
static int TYPE_ID_integer = TID_integer;
static uint32_t TYPE_SIZE_integer = 32;
static int TYPE_ID_array = TID_array;
static uint32_t TYPE_SIZE_array = 64;
static int TYPE_ID_reference = TID_reference;
static uint32_t TYPE_SIZE_reference = 64;

typedef struct _ArrayMeta {
    struct _TYPE* elementType;
    int elements;
} ArrayMeta;

typedef struct _TYPE {
    int id;
    union TYPE_METADATA {
        HashMap* fields;
        ArrayMeta array_info;
        struct _TYPE* referencedType;
    } metadata;
    uint32_t bits;
} TYPE;

typedef struct _FIELDINFO {
    int offset;
    TYPE type;
} FIELDINFO;

static int next_id = 8;
HashMap* idToType;

void initialize();

TYPE getType(char* id);

void addType(char* id, TYPE type);

int getNextID();

typedef struct value {
    TYPE type;
    union VALUE_CONTENTS {
        int INT;
        unsigned long BV;
        bool BOOLEAN;
        float fp;
    } contents;
} VALUE;

VALUE newIntegerVALUE(int value);
VALUE newBooleanVALUE(bool value);
VALUE newRealVALUE(float value);
VALUE newFPVALUE(float value);
VALUE newBitVectorVALUE(unsigned long value, int numBits);
VALUE newRoundingModeVALUE(RoundingMode mode);
#endif //YOUVERIFY_VALUE_H
