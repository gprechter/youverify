//
// Created by Griffin Prechter on 1/6/21.
//

#include "RT_Expression.h"

RT_UnaryExpression newRT_UnaryExpression(UNARY_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_UnaryExpression rtUnaryExpression;
    rtUnaryExpression.op = UnaryOperators[expression.op];
    rtUnaryExpression.operand = newRT_AtomicExpression(expression.operand, symbolTable, lexicalScope);
    return rtUnaryExpression;
}

RT_TernaryExpression newRT_TernaryExpression(TERNARY_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_TernaryExpression rtTernaryExpression;
    rtTernaryExpression.op = TernaryOperators[expression.op];
    rtTernaryExpression.first = newRT_AtomicExpression(expression.first, symbolTable, lexicalScope);
    rtTernaryExpression.second = newRT_AtomicExpression(expression.second, symbolTable, lexicalScope);
    rtTernaryExpression.third = newRT_AtomicExpression(expression.third, symbolTable, lexicalScope);
    return rtTernaryExpression;
}

RT_BinaryExpression newRT_BinaryExpression(BINARY_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_BinaryExpression rtBinaryExpression;
    rtBinaryExpression.op =  BinaryOperators[expression.op];
    rtBinaryExpression.lhs = newRT_AtomicExpression(expression.lhs, symbolTable, lexicalScope);
    rtBinaryExpression.rhs = newRT_AtomicExpression(expression.rhs, symbolTable, lexicalScope);
    return rtBinaryExpression;
}

RT_AtomicExpression newRT_AtomicExpression(ATOMIC_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_AtomicExpression rtAtomicExpression;
    rtAtomicExpression.type = expression.type;
    switch (expression.type) {
        case A_id: {
            rtAtomicExpression.contents.variable = newRT_Variable(expression.contents.identifier, symbolTable, lexicalScope);
            rtAtomicExpression.valueType = rtAtomicExpression.contents.variable.type;
            return rtAtomicExpression;
        }
        case A_val:
        default: {
            rtAtomicExpression.contents.value = newRT_Value(expression.contents.value, symbolTable, lexicalScope);
            rtAtomicExpression.valueType = rtAtomicExpression.contents.value.type;
            return rtAtomicExpression;
        }
    }
}

RT_FunctionCallExpression newRT_FunctionCallExpression(FUNCTION_CALL_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_FunctionCallExpression rtFunctionCallExpression;
    FunctionData* functionData;
    if (!HM_get(symbolTable->functions, expression.name.id, &functionData) && symbolTable->parent != NULL) {
        HM_get(symbolTable->parent->functions, expression.name.id, &functionData);
    }
    rtFunctionCallExpression.index = functionData->index;
    rtFunctionCallExpression.returnType = functionData->returnType;
    rtFunctionCallExpression.numArgs = expression.parameters->size;
    rtFunctionCallExpression.arguments = malloc(sizeof(RT_AtomicExpression) * expression.parameters->size);
    int a_i = 0;
    while(!isEmpty(expression.parameters)) {
        rtFunctionCallExpression.arguments[a_i] = newRT_AtomicExpression(((EXPRESSION *)pop(expression.parameters))->contents.atomicExpression, symbolTable, lexicalScope);
        a_i++;
    }
    return rtFunctionCallExpression;
}

RT_ArrayAccessExpression newRT_ArrayAccessExpression(ARRAY_ACCESS_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_ArrayAccessExpression rtArrayAccessExpression;
    rtArrayAccessExpression.arr = newRT_Variable(expression.arr, symbolTable, lexicalScope);
    rtArrayAccessExpression.index = newRT_AtomicExpression(expression.index, symbolTable, lexicalScope);
    rtArrayAccessExpression.elemType = *rtArrayAccessExpression.arr.type.metadata.array_info.elementType; //TODO: FIX THIS
    return rtArrayAccessExpression;
}

RT_FieldAccessExpression newRT_FieldAccessExpression(FIELD_ACCESS_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_FieldAccessExpression rtFieldAccessExpression;
    rtFieldAccessExpression.record = newRT_Variable(expression.record, symbolTable, lexicalScope);
    FIELDINFO* fieldinfo;
    HM_get(rtFieldAccessExpression.record.type.metadata.fields, expression.field.id, &fieldinfo);
    rtFieldAccessExpression.offset = fieldinfo->offset;
    rtFieldAccessExpression.elemType = fieldinfo->type;
    return rtFieldAccessExpression;
}

RT_NewArrayExpression newRT_NewArrayExpression(NEW_ARRAY_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_NewArrayExpression rtNewArrayExpression;
    rtNewArrayExpression.type = getType("ARR");
    rtNewArrayExpression.numElems = expression.elements->size;
    rtNewArrayExpression.elements = malloc(sizeof(RT_AtomicExpression) * expression.elements->size);

    int e_i = 0;
    RT_AtomicExpression element;
    while(!isEmpty(expression.elements)) {
        element = newRT_AtomicExpression(((EXPRESSION *)pop(expression.elements))->contents.atomicExpression, symbolTable, lexicalScope);
        TYPE* elementType = malloc(sizeof(TYPE));
        *elementType = element.valueType;
        rtNewArrayExpression.type.metadata.array_info.elementType = elementType;
        rtNewArrayExpression.elements[e_i] = element;
        e_i++;
    }

    return rtNewArrayExpression;
}

RT_MemoryAllocateExpression newRT_MemoryAllocateExpression(MEMORY_ALLOCATE_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_MemoryAllocateExpression rtMemoryAllocateExpression;
    rtMemoryAllocateExpression.words = expression.words;
    return rtMemoryAllocateExpression;
}

RT_DereferenceExpression newRT_DereferenceExpression(DEREFERENCE_EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_DereferenceExpression rtDereferenceExpression;
    rtDereferenceExpression.variable = newRT_Variable(expression.identifier, symbolTable, lexicalScope);
    return rtDereferenceExpression;
}


RT_Expression newRT_Expression(EXPRESSION expression, SYMBOL_TABLE* symbolTable, NAME_SCOPE lexicalScope) {
    RT_Expression rtExpression;
    rtExpression.type = expression.type;
    switch (expression.type) {
        case E_atomic: {
            rtExpression.contents.atomicExpression = newRT_AtomicExpression(expression.contents.atomicExpression, symbolTable, lexicalScope);
            return rtExpression;
        }
        case E_unary: {
            rtExpression.contents.unaryExpression = newRT_UnaryExpression(expression.contents.unaryExpression, symbolTable, lexicalScope);
            return rtExpression;
        }
        case E_binary: {
            rtExpression.contents.binaryExpression = newRT_BinaryExpression(expression.contents.binaryExpression, symbolTable, lexicalScope);
            return rtExpression;
        }
        case E_ternary: {
            rtExpression.contents.ternaryExpression = newRT_TernaryExpression(expression.contents.ternaryExpression, symbolTable, lexicalScope);
            return rtExpression;
        }
        case E_call: {
            rtExpression.contents.callExpression = newRT_FunctionCallExpression(expression.contents.callExpression, symbolTable, lexicalScope);
            return rtExpression;
        }
        case E_newarr: {
            rtExpression.contents.newArrayExpression = newRT_NewArrayExpression(expression.contents.newArrayExpression, symbolTable, lexicalScope);
            return rtExpression;
        }
        case E_arracc: {
            rtExpression.contents.arrayAccessExpression = newRT_ArrayAccessExpression(expression.contents.arrayAccessExpression, symbolTable, lexicalScope);
            return rtExpression;
        }
        case E_facc: {
            rtExpression.contents.fieldAccessExpression = newRT_FieldAccessExpression(expression.contents.fieldAccessExpression, symbolTable, lexicalScope);
            return rtExpression;
        }
        case E_malloc: {
            rtExpression.contents.memoryAllocateExpression = newRT_MemoryAllocateExpression(expression.contents.memoryAllocateExpression, symbolTable, lexicalScope);
            return rtExpression;
        }
        case E_deref: {
            rtExpression.contents.dereferenceExpression = newRT_DereferenceExpression(expression.contents.dereferenceExpression, symbolTable, lexicalScope);
            return rtExpression;
        }
        default:
            return rtExpression;
    }
}