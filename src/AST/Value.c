//
// Created by Griffin Prechter on 10/29/20.
//

#include "Value.h"

VALUE newIntegerVALUE(int value) {
    VALUE s;
    s.type = getType("INT");
    s.contents.INT = value;
    return s;
}

void initialize(){
idToType = newHashMap();

TYPE* TYPE_boolean = malloc(sizeof(TYPE));
TYPE_boolean->id = 0;
TYPE_boolean->bits = 32;

TYPE* TYPE_integer = malloc(sizeof(TYPE));
TYPE_integer->id = 1;
TYPE_integer->bits = 32;

TYPE* TYPE_array = malloc(sizeof(TYPE));
TYPE_array->id = 2;
TYPE_array->bits = 64;

TYPE* TYPE_reference = malloc(sizeof(TYPE));
TYPE_reference->id = 3;
TYPE_reference->bits = 64;

TYPE* TYPE_real = malloc(sizeof(TYPE));
TYPE_real->id = TID_real;
TYPE_real->bits = sizeof(float) * 8;

TYPE* TYPE_FP = malloc(sizeof(TYPE));
TYPE_FP->id = TID_FP;
TYPE_FP->bits = sizeof(float) * 8;

TYPE* TYPE_RM = malloc(sizeof(TYPE));
TYPE_RM->id = TID_RoundngMode;
TYPE_RM->bits = 32;

HM_put(idToType, "BOOL", (void *) TYPE_boolean);
HM_put(idToType, "INT", (void *) TYPE_integer);
HM_put(idToType, "ARR", (void *) TYPE_array);
HM_put(idToType, "REAL", (void *) TYPE_real);
HM_put(idToType, "FP", (void *) TYPE_FP);
HM_put(idToType, "REF", (void *) TYPE_reference);
HM_put(idToType, "RM", (void *) TYPE_reference);
}

TYPE getType(char* id) {
    TYPE* type;
    HM_get(idToType, id, &type);
    return *type;
}

void addType(char* id, TYPE type) {
    TYPE* typePtr = malloc(sizeof(TYPE));
    *typePtr = type;
    HM_put(idToType, id, typePtr);
}

int getNextID() {
    int next = next_id;
    next_id++;
    return next;
}

VALUE newBooleanVALUE(bool value) {
    VALUE s;
    s.type = getType("BOOL");
    s.contents.BOOLEAN = value;
    return s;
}

VALUE newRealVALUE(float value) {
    VALUE s;
    s.type = getType("REAL");
    s.contents.fp = value;
    return s;
}

VALUE newFPVALUE(float value) {
    VALUE s;
    s.type = getType("FP");
    s.contents.fp = value;
    return s;
}

VALUE newBitVectorVALUE(unsigned long value, int numBits){
    VALUE v;
    TYPE type;
    type.id = TID_bitvector;
    type.bits = numBits;
    v.contents.BV = value;
    v.type = type;
    return v;
}

VALUE newRoundingModeVALUE(RoundingMode mode) {
    VALUE v;
    v.type = getType("FP");
    v.contents.INT = mode;
    return v;
}
