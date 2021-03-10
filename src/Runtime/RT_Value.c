//
// Created by Griffin Prechter on 1/2/21.
//

#include "RT_Value.h"
#include "Utilities.h"

RT_Value newRT_Value(VALUE value, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_Value RT_value;
    RT_value.type = value.type;
    RT_value.isSymbol = value.isSymbol;
    switch(value.type.id) {
        case TID_integer:
            return newRT_IntegerValue(value.contents.INT);
        case TID_boolean: {
            RT_value = newRT_BooleanValue(value.contents.BOOLEAN);
            RT_value.isSymbol = value.isSymbol;
            return RT_value;
        }
        case TID_bitvector: {
            RT_value.content = malloc(rUB(RT_value.type.bits) / 8);
            *((unsigned long*)RT_value.content) = value.contents.BV;
            return RT_value;
        }
        case TID_real: {
            return newRT_RealValue(value.contents.fp);
        }
        default:
            return RT_value;
    }
}

RT_Value newRT_IntegerValue(int value) {
    RT_Value RT_value;
    RT_value.type = getType("INT");
    RT_value.content = malloc(RT_value.type.bits / 8);
    *((uint32_t *) RT_value.content) = value;
    return RT_value;
}
RT_Value newRT_BooleanValue(bool value) {
    RT_Value RT_value;
    RT_value.type = getType("BOOL");
    RT_value.content = malloc(RT_value.type.bits / 8);
    *((bool*) RT_value.content) = value;
    return RT_value;
}
RT_Value newRT_FPValue(float value) {
    RT_Value RT_value;
    RT_value.type = getType("FP");
    RT_value.content = malloc(RT_value.type.bits / 8);
    *((float*) RT_value.content) = value;
    return RT_value;
}
RT_Value newRT_RealValue(float value) {
    RT_Value RT_value;
    RT_value.type = getType("REAL");
    RT_value.content = malloc(RT_value.type.bits / 8);
    *((float*) RT_value.content) = value;
    return RT_value;
}
RT_Value newRT_BitVectorValue(unsigned long value, int numBits) {
    RT_Value RT_value;
    RT_value.type.id = TID_bitvector;
    RT_value.type.bits = numBits;
    RT_value.content = malloc(rUB(numBits) / 8);
    *((unsigned long *) RT_value.content) = value;
    return RT_value;
}

RT_Value newRT_ArrayRefValue(uint8_t* value) {
    RT_Value RT_value;
    RT_value.type = getType("ARR");
    RT_value.content = malloc(RT_value.type.bits / 8);
    *((uint8_t**) RT_value.content) = value;
    return RT_value;
}

RT_Value newRT_ReferenceValue(uint8_t* value) {
    RT_Value RT_value;
    RT_value.type = getType("REF");
    RT_value.content = malloc(RT_value.type.bits / 8);
    *((uint8_t**) RT_value.content) = value;
    return RT_value;
}

RT_Value newRT_EmptyValue(TYPE type) {
    RT_Value RT_value;
    RT_value.type = type;
    return RT_value;
}