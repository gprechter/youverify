import sys
import json
from antlr4 import *

from YouVerifyVisitorOld import YouVerifyVisitor
from YouVerifyLexer import YouVerifyLexer
from YouVerifyParser import YouVerifyParser

from pysmt.shortcuts import TRUE, is_sat, simplify, get_model, get_free_variables, Solver, Int
from pysmt.typing import _BoolType
from AST import Program, Variable, array_to_length_map, YouVerifyArray, TCContext
from State import State, Frame, DefaultState
from SMTLibUtil import *

def main(argv):
    input_stream = FileStream(argv[1])
    lexer = YouVerifyLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = YouVerifyParser(stream)
    variables, functions, statements, labels, records = YouVerifyVisitor().visitProgram(parser.program())
    program = Program(statements, variables, labels, functions)

    State.records = records
    not_sanitary = False
    '''
    global_tc_context = TCContext({k: v.name for k, v in program.variables.items()}, functions)
    for i, stmt in enumerate(program.statements):
        _, err = stmt.type_check(global_tc_context)
        if err:
            not_sanitary = True
            print(f"line {i}: {err}")
    for function in program.functions.values():
        local_variable_map = {k: v.name for k, v in program.variables.items()}
        local_variable_map.update({k: v.name for k, v in function.params.items()})
        local_variable_map.update({k: v.name for k, v in function.variables.items()})
        local_tc_context = TCContext(local_variable_map, functions, function.return_value)
        for i, stmt in enumerate(function.statements):
            _, err = stmt.type_check(local_tc_context)
            if err:
                not_sanitary = True
                print(f"In function {function.name}, line {i}: {err}")
    if not_sanitary:
        print('\033[91m' + "FAILED TO RUN BECAUSE OF TYPE ERRORS." + '\033[0m')
        return []
    '''

    def exec(program):
        state = DefaultState([State(TRUE(), [Frame(program, 0, {k: [v.name, None] for k, v in program.variables.copy().items()}, None)])])
        while state.next_state():
            stmt = state.current_statement
            if is_sat(state.path_cond):
                states.extend([s for s in stmt.exec(state)])
           # if is_sat(state.path_cond):
                #print(stmt)
        return [s for s in states if is_sat(s.path_cond)]

    return exec(program)

def simplify_smt(value, type):
    if isinstance(value, dict):
        return str({k: simplify_smt(v) for k, v in value.items()})
    elif isinstance(value, YouVerifyArray):
        if value.length:
            return simplify(value.get_array())
    else:
        return simplify(value)

def display_model(state, variables, model, depth = 0):
    if not model:
        return
    for k, v in variables.items():
        if isinstance(v[0], str):
            elems = State.records[v[0]].elements
            types = State.records[v[0]].types
            if model.get_value(v[1]).constant_value() == 0:
                print(f"{'  ' * depth}{k}: {'null'}")
            else:
                print(f"{'  ' * depth}{k}:")
                display_model(state,
                          {k: [types[elems.index(k)], v] for k, v in state.addr_map[model.get_value(v[1]).constant_value()].items()},
                          model, depth = depth + 1)
        elif isinstance(v[1], YouVerifyArray):
            print(f"{'  ' * depth}{k}: []->{[simplify(model.get_value(v[1].get_array())).array_value_get(Int(i)) for i in range(simplify(model.get_value(v[1].length)).constant_value())]}")
        else:
            print(f"{'  ' * depth}{k}: {model.get_value(v[1])}")
    #print("MODEL", model)

def display_states_smt2(states):
    for i, state in enumerate(states):
        state_desc = f"{i}\t" + str({k: simplify_smt(v[1], v[0]) for k, v in state.head_frame().variables.items()})
        print("" + "=" * 40 + "")
        #print(state_desc)
        print(i)
        #print("Memory Map: ", state.addr_map)
        print("=" * 40)
        print("(set-option :produce-models true)")
        print('\n'.join(gen_declare_const(state.path_cond)))
        print(gen_assert(simplify(state.path_cond)))
        display_model(state, state.head_frame().variables, get_model(state.path_cond))

def concrete_evaluation(states):
    state = states[0]
    assert all([simplify(v[1]).is_constant() for k, v in state.head_frame().variables.items() if not isinstance(v[1], YouVerifyArray)]), "All variables must be constant."
    return json.dumps({k: simplify(v[1]).constant_value() if not isinstance(v[1], YouVerifyArray) else
                    [simplify(get_model(state.path_cond).get_value(v[1].get_array())).array_value_get(Int(i)).constant_value() for i in range(simplify(v[1].length).constant_value())]
                       for k, v in state.head_frame().variables.items()})

if __name__ == '__main__':
    display_states_smt2(main(sys.argv))