//
// Created by Griffin Prechter on 3/9/21.
//

#ifndef YOUVERIFY_RT_ENVIRONMENT_H
#define YOUVERIFY_RT_ENVIRONMENT_H

#include "RT_Value.h"

typedef struct _RT_Environment {
    struct _RT_environment* parent;
    RT_Value* variables;
    FUNCTION* functions;
}RT_Environment;

RT_Environment createRT_Environment(RT_Environment* parent, int numVariables, FUNCTION* functions);

RT_Environment createChildEnvironment(RT_Environment* parent, int numVariables);

#endif //YOUVERIFY_RT_ENVIRONMENT_H
