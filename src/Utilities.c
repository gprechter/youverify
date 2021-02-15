//
// Created by Griffin Prechter on 2/8/21.
//

#include "Utilities.h"

int rUB(int bits) {
    return ((bits + 31) / 32) * 32;
}

int minInt(int a, int b) {
    return a < b ? a : b;
}