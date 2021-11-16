//
// Created by Griffin Prechter on 2/8/21.
//

#include "BitVectorOperators.h"
#include "ConsumeValue.h"
#include "Utilities.h"

unsigned long BV2Nat(RT_Value operand) {
    unsigned long value = *((unsigned long*) operand.content);
    free(operand.content);
    return value;
}

RT_Value Nat2BV(unsigned long operand, int numBits) {
    return newRT_BitVectorValue(operand, numBits);
}


RT_Value UnaryBV2NatOperation(RT_Value operand) {
    return newRT_IntegerValue(*((int *)operand.content));
}

RT_Value UnaryNat2BVOperation(RT_Value operand) {
    return newRT_BitVectorValue(*((int *)operand.content), 32);
}

RT_Value UnaryBVNotOperation(RT_Value operand) {
    return Nat2BV(~BV2Nat(operand), operand.type.bits);
}

RT_Value UnaryBVNegOperation(RT_Value operand) {
    return Nat2BV(-BV2Nat(operand), operand.type.bits);
}

RT_Value BinaryBVConcatOperation(RT_Value left, RT_Value right) {
    int totalBits = minInt(left.type.bits + right.type.bits, 64);
    unsigned long leftValue = BV2Nat(left);
    unsigned long rightValue = BV2Nat(right);
    unsigned long resultValue = (rightValue << left.type.bits) | leftValue;
    return Nat2BV(resultValue, totalBits);
}
RT_Value BinaryBVAndOperation(RT_Value left, RT_Value right) {
    return Nat2BV(BV2Nat(left) & BV2Nat(right), left.type.bits);
}
RT_Value BinaryBVOrOperation(RT_Value left, RT_Value right) {
    return Nat2BV(BV2Nat(left) | BV2Nat(right), left.type.bits);
}
RT_Value BinaryBVAddOperation(RT_Value left, RT_Value right) {
    return Nat2BV(BV2Nat(left) + BV2Nat(right), left.type.bits);
}
RT_Value BinaryBVMulOperation(RT_Value left, RT_Value right) {
    return Nat2BV(BV2Nat(left) * BV2Nat(right), left.type.bits);
}
RT_Value BinaryBVDivOperation(RT_Value left, RT_Value right) {
    unsigned long leftValue = BV2Nat(left);
    unsigned long rightValue = BV2Nat(right);
    return Nat2BV(rightValue == 0 ? 1 : (leftValue / rightValue), left.type.bits);
}
RT_Value BinaryBVRemOperation(RT_Value left, RT_Value right) {
    unsigned long leftValue = BV2Nat(left);
    unsigned long rightValue = BV2Nat(right);
    return Nat2BV(rightValue == 0 ? leftValue : (leftValue % rightValue), left.type.bits);
}

RT_Value BinaryBVShlOperation(RT_Value left, RT_Value right) {
    return Nat2BV(BV2Nat(left) << BV2Nat(right), left.type.bits);
}
RT_Value BinaryBVLshrOperation(RT_Value left, RT_Value right) {
    return Nat2BV(BV2Nat(left) >> BV2Nat(right), left.type.bits);
}
RT_Value BinaryBVUltOperation(RT_Value left, RT_Value right) {
    return newRT_BooleanValue(BV2Nat(left) < BV2Nat(right));
}

unsigned long genMask(int maskLen) {
    unsigned long mask = 0;
    for (int i = 0; i < maskLen; i++) {
        mask = mask << 1 | 1;
    }
    return mask;
}

RT_Value TernaryBVExtractOperation(RT_Value first, RT_Value second, RT_Value third) {
    unsigned long value = BV2Nat(third);
    int i = consumeValueAsInteger(first);
    int j = consumeValueAsInteger(second);
    return Nat2BV((value >> i) & genMask(j - i + 1), j - i + 1);
}