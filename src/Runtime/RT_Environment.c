//
// Created by Griffin Prechter on 3/9/21.
//

#include "RT_Environment.h"

RT_Environment createRT_Environment(RT_Environment* parent, int numVariables, FUNCTION* functions) {
    RT_Environment newEnvironment;
    newEnvironment.parent = parent;
    newEnvironment.variables = malloc(sizeof(RT_Value) * numVariables);
    newEnvironment.functions = functions;
}

RT_Environment createChildEnvironment(RT_Environment* parent, int numVariables) {
    return createRT_Environment(parent, numVariables, parent->functions);
}