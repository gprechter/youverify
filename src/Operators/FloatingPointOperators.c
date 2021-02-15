//
// Created by Griffin Prechter on 2/8/21.
//

#include <math.h>
#include <fenv.h>
#include "FloatingPointOperators.h"
#include "ConsumeValue.h"

RT_Value UnaryFPAbsOperation(RT_Value operand) {
    return newRT_FPValue(fabsf(consumeValueAsFP(operand)));
}
RT_Value UnaryFPNegOperation(RT_Value operand) {
    return newRT_FPValue(-(consumeValueAsFP(operand)));
}
RT_Value UnaryFPIsNormalOperation(RT_Value operand) {
    return newRT_BooleanValue(false);//Todo
}
RT_Value UnaryFPIsSubnormalOperation(RT_Value operand) {
    return newRT_BooleanValue(false);//Todo
}
RT_Value UnaryFPIsZeroOperation(RT_Value operand) {
    return newRT_BooleanValue(false);//Todo
}
RT_Value UnaryFPIsInfiniteOperation(RT_Value operand) {
    return newRT_BooleanValue(false);//Todo
}
RT_Value UnaryFPIsNaNOperation(RT_Value operand) {
    return newRT_BooleanValue(false);//Todo
}
RT_Value UnaryFPIsNegativeOperation(RT_Value operand) {
    return newRT_BooleanValue(false); //Todo
}
RT_Value UnaryFPIsPositiveOperation(RT_Value operand) {
    return newRT_BooleanValue(false); //Todo
}
RT_Value UnaryToFPOperation(RT_Value operand) {
    if (operand.type.id == TID_real) {
        return newRT_FPValue(consumeValueAsReal(operand));
    }
    return newRT_IntegerValue(0); // todo
}

RT_Value TernaryFPAddOperation(RT_Value first, RT_Value second, RT_Value third) {
    return newRT_FPValue(consumeValueAsFP(second) + consumeValueAsFP(third));
}
RT_Value TernaryFPSubOperation(RT_Value first, RT_Value second, RT_Value third) {
    return newRT_FPValue(consumeValueAsFP(second) - consumeValueAsFP(third));
}
RT_Value TernaryFPMulOperation(RT_Value first, RT_Value second, RT_Value third)  {
    return newRT_FPValue(consumeValueAsFP(second) * consumeValueAsFP(third));
}
RT_Value TernaryFPDivOperation(RT_Value first, RT_Value second, RT_Value third) {
    return newRT_FPValue(consumeValueAsFP(second) / consumeValueAsFP(third));
}

RT_Value BinaryFPRemOperation(RT_Value left, RT_Value right) {
    return newRT_FPValue(fmodf(consumeValueAsFP(left), consumeValueAsFP(right)));
}
RT_Value BinaryFPSqrtOperation(RT_Value left, RT_Value right) {
    return newRT_FPValue(sqrtf(consumeValueAsFP(right)));
}
RT_Value BinaryFPRoundToIntegralOperation(RT_Value left, RT_Value right) {
    return newRT_FPValue(roundf(consumeValueAsFP(right)));
}
RT_Value BinaryFPMinOperation(RT_Value left, RT_Value right) {
    return newRT_FPValue(fminf(consumeValueAsFP(left), consumeValueAsFP(right)));
}
RT_Value BinaryFPMaxOperation(RT_Value left, RT_Value right) {
    return newRT_FPValue(fmaxf(consumeValueAsFP(left), consumeValueAsFP(right)));
}
RT_Value BinaryFPLeqOperation(RT_Value left, RT_Value right)  {
    return newRT_FPValue((consumeValueAsFP(left) <= consumeValueAsFP(right)));
}
RT_Value BinaryFPLtOperation(RT_Value left, RT_Value right) {
    return newRT_FPValue((consumeValueAsFP(left) < consumeValueAsFP(right)));
}
RT_Value BinaryFPGeqOperation(RT_Value left, RT_Value right) {
    return newRT_FPValue((consumeValueAsFP(left) >= consumeValueAsFP(right)));
}
RT_Value BinaryFPGtOperation(RT_Value left, RT_Value right) {
    return newRT_FPValue((consumeValueAsFP(left) > consumeValueAsFP(right)));
}
RT_Value BinaryFPEqOperation(RT_Value left, RT_Value right) {
    return newRT_FPValue((consumeValueAsFP(left) == consumeValueAsFP(right)));
}
RT_Value BinaryToFPOperation(RT_Value left, RT_Value right) {
    if (right.type.id == TID_real) {
        return newRT_FPValue(consumeValueAsReal(right));
    }
    return newRT_IntegerValue(0); // todo
}