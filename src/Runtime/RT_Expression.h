//
// Created by Griffin Prechter on 1/6/21.
//

#ifndef YOUVERIFY_RT_EXPRESSION_H
#define YOUVERIFY_RT_EXPRESSION_H

#include "AST/Expression.h"
#include "Runtime/Expressions/RT_AtomicExpression.h"
#include "Runtime/Expressions/RT_BinaryExpression.h"
#include "Runtime/Expressions/RT_TernaryExpression.h"
#include "Runtime/Expressions/RT_UnaryExpression.h"
#include "Runtime/Expressions/RT_FunctionCallExpression.h"
#include "Runtime/Expressions/RT_ArrayAccessExpression.h"
#include "Runtime/Expressions/RT_NewArrayExpression.h"
#include "Runtime/Expressions/RT_FieldAccessExpression.h"
#include "Runtime/Expressions/RT_MemoryAllocateExpression.h"
#include "Runtime/Expressions/RT_DerefernceExpression.h"

typedef struct _RT_Expression {
    EXPRESSION_TYPE type;
    union _RT_ExpressionContents {
        RT_AtomicExpression atomicExpression;
        RT_UnaryExpression unaryExpression;
        RT_BinaryExpression binaryExpression;
        RT_TernaryExpression ternaryExpression;
        RT_FunctionCallExpression callExpression;
        RT_NewArrayExpression newArrayExpression;
        RT_ArrayAccessExpression arrayAccessExpression;
        RT_FieldAccessExpression fieldAccessExpression;
        RT_MemoryAllocateExpression memoryAllocateExpression;
        RT_DereferenceExpression dereferenceExpression;
    } contents;
} RT_Expression;

RT_FunctionCallExpression newRT_FunctionCallExpression(FUNCTION_CALL_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
RT_UnaryExpression newRT_UnaryExpression(UNARY_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
RT_TernaryExpression newRT_TernaryExpression(TERNARY_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
RT_BinaryExpression newRT_BinaryExpression(BINARY_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
RT_AtomicExpression newRT_AtomicExpression(ATOMIC_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
RT_NewArrayExpression newRT_NewArrayExpression(NEW_ARRAY_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
RT_ArrayAccessExpression newRT_ArrayAccessExpression(ARRAY_ACCESS_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
RT_FieldAccessExpression newRT_FieldAccessExpression(FIELD_ACCESS_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
RT_MemoryAllocateExpression newRT_MemoryAllocateExpression(MEMORY_ALLOCATE_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
RT_DereferenceExpression newRT_DereferenceExpression(DEREFERENCE_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);

RT_Expression newRT_Expression(EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope);
#endif //YOUVERIFY_RT_EXPRESSION_H
