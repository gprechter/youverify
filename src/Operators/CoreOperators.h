//
// Created by Griffin Prechter on 2/7/21.
//

#ifndef YOUVERIFY_COREOPERATORS_H
#define YOUVERIFY_COREOPERATORS_H

#include "Runtime/RT_Value.h"
#include "DSEState/DSEState.h"

SymbolicExpression UnaryNotOperation(SymbolicExpression symbolicExpression);

SymbolicExpression BinaryImpliesOperation(SymbolicExpression left, SymbolicExpression right);
SymbolicExpression BinaryAndOperation(SymbolicExpression left, SymbolicExpression right);
SymbolicExpression BinaryOrOperation(SymbolicExpression left, SymbolicExpression right);
SymbolicExpression BinaryXorOperation(SymbolicExpression left, SymbolicExpression right);
SymbolicExpression BinaryEqualsOperation(SymbolicExpression left, SymbolicExpression right);
SymbolicExpression BinaryDistinctOperation(SymbolicExpression left, SymbolicExpression right);

RT_Value TernaryITEOperation(RT_Value first, RT_Value second, RT_Value third);

#endif //YOUVERIFY_COREOPERATORS_H
