//
// Created by Griffin Prechter on 10/29/20.
//

#include "Value.h"

VALUE newIntegerVALUE(int value) {
    VALUE s;
    s.type = VALUE_TYPE_integer;
    s.contents.INT = value;
    return s;
}

VALUE newBooleanVALUE(bool value) {
    VALUE s;
    s.type = VALUE_TYPE_boolean;
    s.contents.BOOLEAN = value;
    return s;
}
