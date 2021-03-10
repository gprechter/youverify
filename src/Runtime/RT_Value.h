//
// Created by Griffin Prechter on 1/2/21.
//

#ifndef YOUVERIFY_RT_VALUE_H
#define YOUVERIFY_RT_VALUE_H

#include "AST/Identifier.h"
#include "Analyze/SymbolTable.h"
#include <stdint.h>

typedef struct _RT_Value {
    TYPE type;
    bool isSymbol;
    uint8_t* content;
    /*union CONTENTS {
        int integer;
        bool boolean;
        uint8_t* arr_ref;
    } contents;*/
} RT_Value;

RT_Value newRT_Value(VALUE value, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
RT_Value newRT_IntegerValue(int value);
RT_Value newRT_BooleanValue(bool value);
RT_Value newRT_RealValue(float value);
RT_Value newRT_FPValue(float value);
RT_Value newRT_BitVectorValue(unsigned long value, int numBits);
RT_Value newRT_ArrayRefValue(uint8_t* value);
RT_Value newRT_ReferenceValue(uint8_t* value);
RT_Value newRT_EmptyValue(TYPE type);

#endif //YOUVERIFY_RT_VALUE_H
