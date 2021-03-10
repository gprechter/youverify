//
// Created by Griffin Prechter on 2/7/21.
//

#include "CoreOperators.h"
#include "ConsumeValue.h"

SymbolicExpression UnaryNotOperation(SymbolicExpression symbolicExpression) {
    SymbolicExpression newSymbolicExpression;
    newSymbolicExpression.type = combination;
    newSymbolicExpression.first = "not";
    newSymbolicExpression.numRest = 1;
    newSymbolicExpression.rest = malloc(sizeof(SymbolicExpression));
    newSymbolicExpression.rest[0] = symbolicExpression;
    return newSymbolicExpression;
}

SymbolicExpression BinaryImpliesOperation(SymbolicExpression left, SymbolicExpression right) {
    SymbolicExpression newSymbolicExpression;
    newSymbolicExpression.type = combination;
    newSymbolicExpression.first = "=>";
    newSymbolicExpression.numRest = 2;
    newSymbolicExpression.rest = malloc(sizeof(SymbolicExpression) * 2);
    newSymbolicExpression.rest[0] = left;
    newSymbolicExpression.rest[1] = right;
    return newSymbolicExpression;
}

SymbolicExpression BinaryAndOperation(SymbolicExpression left, SymbolicExpression right) {
    SymbolicExpression newSymbolicExpression;
    newSymbolicExpression.type = combination;
    newSymbolicExpression.first = "and";
    newSymbolicExpression.numRest = 2;
    newSymbolicExpression.rest = malloc(sizeof(SymbolicExpression) * 2);
    newSymbolicExpression.rest[0] = left;
    newSymbolicExpression.rest[1] = right;
    return newSymbolicExpression;
}

SymbolicExpression BinaryOrOperation(SymbolicExpression left, SymbolicExpression right) {
    SymbolicExpression newSymbolicExpression;
    newSymbolicExpression.type = combination;
    newSymbolicExpression.first = "or";
    newSymbolicExpression.numRest = 2;
    newSymbolicExpression.rest = malloc(2 * sizeof(SymbolicExpression));
    newSymbolicExpression.rest[0] = left;
    newSymbolicExpression.rest[1] = right;
    return newSymbolicExpression;
}

SymbolicExpression BinaryXorOperation(SymbolicExpression left, SymbolicExpression right) {
    SymbolicExpression newSymbolicExpression;
    newSymbolicExpression.type = combination;
    newSymbolicExpression.first = "xor";
    newSymbolicExpression.numRest = 2;
    newSymbolicExpression.rest = malloc(sizeof(SymbolicExpression) * 2);
    newSymbolicExpression.rest[0] = left;
    newSymbolicExpression.rest[1] = right;
    return newSymbolicExpression;
}

SymbolicExpression BinaryEqualsOperation(SymbolicExpression left, SymbolicExpression right) {
    SymbolicExpression newSymbolicExpression;
    newSymbolicExpression.type = combination;
    newSymbolicExpression.first = "=";
    newSymbolicExpression.numRest = 2;
    newSymbolicExpression.rest = malloc(sizeof(SymbolicExpression) * 2);
    newSymbolicExpression.rest[0] = left;
    newSymbolicExpression.rest[1] = right;
    return newSymbolicExpression;
}

SymbolicExpression BinaryDistinctOperation(SymbolicExpression left, SymbolicExpression right) {
    SymbolicExpression newSymbolicExpression;
    newSymbolicExpression.type = combination;
    newSymbolicExpression.first = "distinct";
    newSymbolicExpression.numRest = 2;
    newSymbolicExpression.rest = malloc(sizeof(SymbolicExpression) * 2);
    newSymbolicExpression.rest[0] = left;
    newSymbolicExpression.rest[1] = right;
    return newSymbolicExpression;
}

RT_Value TernaryITEOperation(RT_Value first, RT_Value second, RT_Value third) {
    RT_Value result;
    if (consumeValueAsBoolean(first)) {
        result = second;
        free(third.content);
    } else {
        result = third;
        free(second.content);
    }
    return result;
}

