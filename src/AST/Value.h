//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_VALUE_H
#define YOUVERIFY_VALUE_H

#include <stdbool.h>

typedef enum valuetype {VALUE_TYPE_boolean, VALUE_TYPE_integer, VALUE_TYPE_unknown} VALUE_TYPE;

typedef struct value {
    VALUE_TYPE type;
    union VALUE_CONTENTS {
        int INT;
        bool BOOLEAN;
    } contents;
} VALUE;

VALUE newIntegerVALUE(int value);
VALUE newBooleanVALUE(bool value);

#endif //YOUVERIFY_VALUE_H
