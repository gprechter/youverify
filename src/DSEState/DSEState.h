//
// Created by Griffin Prechter on 3/7/21.
//

#ifndef YOUVERIFY_DSESTATE_H
#define YOUVERIFY_DSESTATE_H

typedef enum _SymbolicExpressionType {atom, combination} SymbolicExpressionType;

typedef struct _SymbolicExpression {
    SymbolicExpressionType type;
    char *first;
    int numRest;
    struct _SymbolicExpression* rest;
} SymbolicExpression;


typedef struct _DSEState {
    int pc;
    SymbolicExpression pathCondition;
    SymbolicExpression* variables;
} DSEState;

#endif //YOUVERIFY_DSESTATE_H
