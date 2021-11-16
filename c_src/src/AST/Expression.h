//
// Created by Griffin Prechter on 10/29/20.
//

#ifndef YOUVERIFY_EXPRESSION_H
#define YOUVERIFY_EXPRESSION_H

#include "Operators/Operator.h"
#include "Expressions/AtomicExpression.h"
#include "Expressions/UnaryExpression.h"
#include "Expressions/BinaryExpression.h"
#include "Expressions/TernaryExpression.h"
#include "Expressions/FunctionCallExpression.h"
#include "Expressions/NewArrayExpression.h"
#include "Expressions/ArrayAccessExpression.h"
#include "Expressions/FieldAccessExpression.h"
#include "Expressions/MemoryAllocateExpression.h"
#include "Expressions/DereferenceExpression.h"

typedef enum expressiontype {E_atomic, E_unary, E_binary, E_ternary, E_call, E_newarr, E_arracc, E_facc, E_malloc, E_deref} EXPRESSION_TYPE;

typedef struct expression {
    EXPRESSION_TYPE type;
    union EXPRESSION_CONTENTS {
        ATOMIC_EXPRESSION atomicExpression;
        UNARY_EXPRESSION unaryExpression;
        BINARY_EXPRESSION binaryExpression;
        TERNARY_EXPRESSION ternaryExpression;
        FUNCTION_CALL_EXPRESSION callExpression;
        NEW_ARRAY_EXPRESSION newArrayExpression;
        ARRAY_ACCESS_EXPRESSION arrayAccessExpression;
        FIELD_ACCESS_EXPRESSION fieldAccessExpression;
        MEMORY_ALLOCATE_EXPRESSION memoryAllocateExpression;
        DEREFERENCE_EXPRESSION dereferenceExpression;
    } contents;
} EXPRESSION;

EXPRESSION newATOMIC_EXPRESSION(ATOMIC_EXPRESSION atomicExpression);

EXPRESSION newUNARY_EXPRESSION(UnaryOperatorType op, ATOMIC_EXPRESSION operand);

EXPRESSION newBINARY_EXPRESSION(ATOMIC_EXPRESSION lhs, BinaryOperatorType op, ATOMIC_EXPRESSION rhs);

EXPRESSION newTERNARY_EXPRESSION(TernaryOperatorType op, ATOMIC_EXPRESSION first, ATOMIC_EXPRESSION second, ATOMIC_EXPRESSION third);

EXPRESSION newFunctionCallExpression(Identifier name, QueuePtr parameters);

EXPRESSION newNewArrayExpression(QueuePtr elements);

EXPRESSION newArrayAccessExpression(Identifier arr, ATOMIC_EXPRESSION index);

EXPRESSION newFieldAccessExpression(Identifier record, Identifier field);

EXPRESSION newDereferenceExpression(Identifier identifier);

EXPRESSION newMemoryAllocateExpression(int words);

#endif //YOUVERIFY_EXPRESSION_H
