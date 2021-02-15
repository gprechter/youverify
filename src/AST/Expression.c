//
// Created by Griffin Prechter on 10/29/20.
//

#include "Expression.h"

EXPRESSION newATOMIC_EXPRESSION(ATOMIC_EXPRESSION atomicExpression) {
    EXPRESSION e;
    e.type = E_atomic;
    e.contents.atomicExpression = atomicExpression;
    return e;
}

EXPRESSION newBINARY_EXPRESSION(ATOMIC_EXPRESSION lhs, BinaryOperatorType op, ATOMIC_EXPRESSION rhs) {
    EXPRESSION e;
    e.type = E_binary;
    BINARY_EXPRESSION b;
    b.lhs = lhs;
    b.op = op;
    b.rhs = rhs;
    e.contents.binaryExpression = b;
    return e;
}

EXPRESSION newUNARY_EXPRESSION(UnaryOperatorType op, ATOMIC_EXPRESSION operand) {
    EXPRESSION e;
    e.type = E_unary;
    UNARY_EXPRESSION u;
    u.op = op;
    u.operand = operand;
    e.contents.unaryExpression = u;
    return e;
}

EXPRESSION newTERNARY_EXPRESSION(TernaryOperatorType op, ATOMIC_EXPRESSION first, ATOMIC_EXPRESSION second, ATOMIC_EXPRESSION third) {
    EXPRESSION e;
    e.type = E_ternary;
    TERNARY_EXPRESSION t;
    t.op = op;
    t.first = first;
    t.second = second;
    t.third = third;
    e.contents.ternaryExpression = t;
    return e;
}

EXPRESSION newFunctionCallExpression(Identifier name, QueuePtr parameters) {
    EXPRESSION e;
    e.type = E_call;
    FUNCTION_CALL_EXPRESSION functionCallExpression;
    functionCallExpression.name = name;
    functionCallExpression.parameters = parameters;
    e.contents.callExpression = functionCallExpression;
    return e;
}

EXPRESSION newNewArrayExpression(QueuePtr elements) {
    EXPRESSION e;
    e.type = E_newarr;
    NEW_ARRAY_EXPRESSION newArrayExpression;
    newArrayExpression.elements = elements;
    e.contents.newArrayExpression = newArrayExpression;
    return e;
}

EXPRESSION newArrayAccessExpression(Identifier arr, ATOMIC_EXPRESSION index) {
    EXPRESSION e;
    e.type = E_arracc;
    ARRAY_ACCESS_EXPRESSION arrayAccessExpression;
    arrayAccessExpression.arr = arr;
    arrayAccessExpression.index = index;
    e.contents.arrayAccessExpression = arrayAccessExpression;
    return e;
}

EXPRESSION newFieldAccessExpression(Identifier record, Identifier field) {
    EXPRESSION e;
    e.type = E_facc;
    FIELD_ACCESS_EXPRESSION fieldAccessExpression;
    fieldAccessExpression.record = record;
    fieldAccessExpression.field = field;
    e.contents.fieldAccessExpression = fieldAccessExpression;
    return e;
}

EXPRESSION newMemoryAllocateExpression(int words) {
    EXPRESSION e;
    e.type = E_malloc;
    MEMORY_ALLOCATE_EXPRESSION memoryAllocateExpression;
    memoryAllocateExpression.words = words;
    e.contents.memoryAllocateExpression = memoryAllocateExpression;
    return e;
}

EXPRESSION newDereferenceExpression(Identifier identifier) {
    EXPRESSION e;
    e.type = E_deref;
    DEREFERENCE_EXPRESSION dereferenceExpression;
    dereferenceExpression.identifier = identifier;
    e.contents.dereferenceExpression = dereferenceExpression;
    return e;
}