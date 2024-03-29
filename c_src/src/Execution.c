//
//  Execution.c
//  
//
//  Created by Griffin Prechter on 10/23/20.
//

#include "Execution.h"
#include "LinkedList.h"
#include "Analyze/Function.h"
#include "Utilities.h"
#include <string.h>

RT_Value evalAtom(RT_AtomicExpression expression, RuntimeEnvironment *env) {
    switch (expression.type) {
        case A_id: {
            NAME_SCOPE scope = expression.contents.variable.scope;
            int offset = rUB(expression.contents.variable.index) / 32;
            void* ptr = getVarPointer(scope, offset, env);
            return evaluateAsType(ptr, expression.contents.variable.type);
        }
        case A_val:
        default: {
            RT_Value value;
            value = expression.contents.value;
            uint8_t * newContent = malloc(rUB(value.type.bits) / 8);
            memcpy(newContent, value.content, rUB(value.type.bits) / 8);
            value.content = newContent;
            return value;
        }
    }
}

RT_Value evalExpr(RT_Expression expression, RuntimeEnvironment *env) {
    switch (expression.type) {
        case E_atomic:
            return evalAtom(expression.contents.atomicExpression, env);
        case E_unary: {
            RT_Value operand = evalAtom(expression.contents.unaryExpression.operand, env);
            return (expression.contents.unaryExpression.op)(operand);
        }
        case E_binary: {
            RT_Value left = evalAtom(expression.contents.binaryExpression.lhs, env);
            RT_Value right = evalAtom(expression.contents.binaryExpression.rhs, env);
            return (expression.contents.binaryExpression.op)(left, right);
        }
        case E_call: {
            int i;
            FUNCTION function = env->functions[expression.contents.callExpression.index];

            uint8_t* base_sp = env->sp;
            for(i = 0; i < expression.contents.callExpression.numArgs; i++) {
                RT_Value arg = evalAtom(expression.contents.callExpression.arguments[i], env);
                base_sp = base_sp - rUB(arg.type.bits) / 8;
                assignVariable(base_sp, arg);
            }
            pushActivationFrame(function.symbolTable->totalRequiredBits / 32, env);
            RT_Value returnValue = executeFunction(function, env);
            popActivationFrame(env);

            return returnValue;
        }
        case E_newarr: {

            int numElems = expression.contents.newArrayExpression.numElems;
            uint8_t* ptr = allocate(numElems, env);
            /*for (int i = 0; i < numElems; i++) {
                RT_Value value = evalAtom(expression.contents.newArrayExpression.elements[i], env);
                switch (value.type.id) {
                    case TID_boolean: {
                        ((bool*)ptr)[i] = evalAtom(expression.contents.newArrayExpression.elements[i], env).contents.boolean;
                        break;
                    }
                    case TID_integer: {
                        ((int*)ptr)[i] = evalAtom(expression.contents.newArrayExpression.elements[i], env).contents.integer;
                        break;
                    }
                }
            }*/
            return newRT_ArrayRefValue(ptr);
        }
        case E_arracc: {
            void* ptr = getVarPointer(expression.contents.arrayAccessExpression.arr.scope, rUB(expression.contents.arrayAccessExpression.arr.index) / 32, env);

            RT_Value indexValue = evalAtom(expression.contents.arrayAccessExpression.index, env);
            int index = *((uint32_t *) indexValue.content);
            free(indexValue.content);

            RT_Value arrayReferenceValue = evaluateAsType(ptr, expression.contents.arrayAccessExpression.arr.type);
            uint8_t * arrayReference = *((uint8_t **) arrayReferenceValue.content);
            free(arrayReferenceValue.content);

            int width = rUB(expression.contents.arrayAccessExpression.elemType.bits) / 8;
            return newRT_IntegerValue((int) (arrayReference)[index * width]);

        }
        case E_facc: {
            NAME_SCOPE scope = expression.contents.fieldAccessExpression.record.scope;
            int n = rUB(expression.contents.fieldAccessExpression.record.index) / 32;
            void* ptr = getVarPointer(scope, n, env);
            int fieldOffset = rUB(expression.contents.fieldAccessExpression.offset);
            return evaluateAsType(((char *)ptr) + fieldOffset / 8, expression.contents.fieldAccessExpression.elemType);
        }
        case E_deref: {
            NAME_SCOPE scope = expression.contents.dereferenceExpression.variable.scope;
            int n = rUB(expression.contents.dereferenceExpression.variable.index) / 32;
            void* ptr = getVarPointer(scope, n, env);
            uint8_t * reference = *((uint8_t**) ptr);
            return evaluateAsType(reference, *expression.contents.dereferenceExpression.variable.type.metadata.referencedType);
        }
        case E_malloc: {
            uint8_t* ptr = allocate(expression.contents.memoryAllocateExpression.words, env);
            return newRT_ArrayRefValue(ptr);
        }
        case E_ternary: {
            RT_Value pred = evalAtom(expression.contents.ternaryExpression.first, env);
            RT_Value then = evalAtom(expression.contents.ternaryExpression.second, env);
            RT_Value el = evalAtom(expression.contents.ternaryExpression.third, env);
            return (expression.contents.ternaryExpression.op)(pred, then, el);
        }
    }
}

RT_Value executeFunction(FUNCTION function, RuntimeEnvironment *env) {
    int pc = 0;
    while(pc < function.size) {
        if (function.body[pc].type == RT_assignment) {
            pc = executeAssignment(pc, function.body[pc].contents.assignmentInstruction, env);
        } else if (function.body[pc].type == RT_goto) {
            pc = executeBranch(pc, function.body[pc].contents.gotoInstruction, env);
        } else if (function.body[pc].type == RT_return) {
            return evalExpr(function.body[pc].contents.returnInstruction.expression, env);
        }
    }
    return newRT_EmptyValue(function.returnType);
}

PC executeAssignment(PC pc, RT_AssignmentInstruction instruction, RuntimeEnvironment *env) {
    void * ptr;
    switch (instruction.type) {
        case AI_variable: {
            NAME_SCOPE scope = instruction.destination.variable.scope;
            int offset = rUB(instruction.destination.variable.index) / 32;
            ptr = getVarPointer(scope, offset, env);
            break;
        }
        case AI_array_elem: {
            void* arrPtr = getVarPointer(instruction.destination.arrayAccessExpression.arr.scope, rUB(instruction.destination.arrayAccessExpression.arr.index) / 32, env);

            RT_Value indexValue = evalAtom(instruction.destination.arrayAccessExpression.index, env);
            int index = *((uint32_t *) indexValue.content);
            free(indexValue.content);

            RT_Value arrayReferenceValue = evaluateAsType(arrPtr, instruction.destination.arrayAccessExpression.arr.type);
            uint8_t * arrayReference = *((uint8_t **) arrayReferenceValue.content);
            free(arrayReferenceValue.content);

            int width = rUB(instruction.destination.arrayAccessExpression.elemType.bits) / 8;
            ptr = (arrayReference) + index * width;
            break;
        }
        case AI_field: {
            NAME_SCOPE scope = instruction.destination.fieldAccessExpression.record.scope;
            int n = rUB(instruction.destination.fieldAccessExpression.record.index) / 32;
            int fieldOffset = rUB(instruction.destination.fieldAccessExpression.offset);
            ptr = ((char *)getVarPointer(scope, n, env)) + fieldOffset / 8;
            break;
        }
        case AI_deref: {
            NAME_SCOPE scope = instruction.destination.dereferenceExpression.variable.scope;
            int n = rUB(instruction.destination.dereferenceExpression.variable.index) / 32;
            void* ptrRef = getVarPointer(scope, n, env);
            ptr = *((uint8_t**) ptrRef);
            break;
        }
    }
    RT_Value rhs = evalExpr(instruction.expression, env);
    assignVariable(ptr, rhs);
    return pc + 1;
}

void *getVarPointer(NAME_SCOPE scope, int n, RuntimeEnvironment *env) {
    if (scope == global) {
        return getGlobalVar(n, env);
    } else {
        return getLocalVar(n, env);
    }
}

void assignVariable(void *ptr, RT_Value value) {
    int bytes = rUB(value.type.bits) / 8;
    memcpy(ptr, value.content, bytes);
    free(value.content);
}

RT_Value evaluateAsType(void *ptr, TYPE type) {
    RT_Value value;
    value.type = type;
    value.content = malloc(rUB(value.type.bits) / 8);
    memcpy(value.content, ptr, rUB(value.type.bits) / 8);
    return value;
}

PC executeBranch(PC pc, RT_GotoInstruction instruction, RuntimeEnvironment *env) {
    RT_Value predValue = evalExpr(instruction.predicate, env);
    bool pred = *((bool *)predValue.content);
    free(predValue.content);
    if (predValue.type.id == TID_boolean && pred) {
        return instruction.pc_next;
    } else {
        return pc + 1;
    }
}
