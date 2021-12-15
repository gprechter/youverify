import sys
import os
import json
from antlr4 import *
import pickle
import argparse

from YouVerifyVisitorOld import YouVerifyVisitor
from YouVerifyLexer import YouVerifyLexer
from YouVerifyParser import YouVerifyParser

from pysmt.shortcuts import TRUE, is_sat, simplify, get_model, get_free_variables, Solver, Int
from pysmt.typing import _BoolType
from AST import Program, Variable, array_to_length_map, YouVerifyArray, TCContext
from State import SubState, Frame, DefaultState
from SMTLibUtil import *

def main(file, input):
    input_stream = FileStream(file)
    vars = {}
    if input:
        f = open(f"./out/{os.path.basename(file)}/{input}/{input}.pickle", "rb")
        vars.update(pickle.load(f))
        f.close()
    DefaultState.inputs = vars
    lexer = YouVerifyLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = YouVerifyParser(stream)
    variables, functions, statements, labels, records = YouVerifyVisitor().visitProgram(parser.program())
    program = Program(statements, variables, labels, functions)

    SubState.records = records
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
        state = DefaultState([SubState(TRUE(), [Frame(program, 0, {k: [v.name, None] for k, v in program.variables.copy().items()}, None)])])
        SubState.controller = state
        while state.update_state():
            stmt = state.current_statement
            stmt.exec(state)
        return state

    return exec(program)

def simplify_smt(value, type):
    if isinstance(value, dict):
        return str({k: simplify_smt(v) for k, v in value.items()})
    elif isinstance(value, YouVerifyArray):
        if value.length:
            return simplify(value.get_array())
    else:
        return simplify(value)

def display_model(state, variables, model, file, depth = 0):
    if not model:
        return
    for k, v in variables.items():
        if isinstance(v[0], str):
            elems = SubState.records[v[0]].elements
            types = SubState.records[v[0]].types
            if model.get_value(v[1]).constant_value() == 0:
                print(f"{'  ' * depth}{k}: {'null'}", file=file)
            else:
                print(f"{'  ' * depth}{k}:",file=file)
                display_model(state,
                          {k: [types[elems.index(k)], v] for k, v in state.addr_map[model.get_value(v[1]).constant_value()].items()},
                          model, file, depth = depth + 1)
        elif isinstance(v[1], YouVerifyArray):
            if v[1].length:
                print(f"{'  ' * depth}{k}: []->{[simplify(model.get_value(v[1].get_array())).array_value_get(Int(i)) for i in range(simplify(model.get_value(v[1].length)).constant_value())]}", file=file)
            else:
                print(f"{'  ' * depth}{k}: []->{simplify(model.get_value(v[1].get_array()))}", file=file)
        else:
            print(f"{'  ' * depth}{k}: {model.get_value(v[1])}", file=file)
    #print("MODEL", model)

def display_states_smt2(state, file_name, input):
    for i, s in enumerate(state.sub_states):
        #state_desc = f"{i}\t" + str({k: simplify_smt(v[1], v[0]) for k, v in s.head_frame().variables.items()})

        if input or len(state.sub_states) == 1:
            display_model(s, s.head_frame().variables, get_model(s.path_cond), None)
        else:
            try:
                os.mkdir('./out')
            except FileExistsError:
                pass
            try:
                os.mkdir(f"./out/{os.path.basename(file_name)}")
            except FileExistsError:
                pass
            try:
                os.mkdir(f"./out/{os.path.basename(file_name)}/{i}")
            except FileExistsError:
                pass
            try:
                f = open(f"./out/{os.path.basename(file_name)}/{i}/{i}.trace", "x")
            except FileExistsError:
                f = open(f"./out/{os.path.basename(file_name)}/{i}/{i}.trace", "w")
            f.write(s.trace)
            f.close()
            model = get_model(s.path_cond)
            vars = {}

            for v in get_free_variables(s.path_cond):
                if v.symbol_name() not in vars:
                    vars[v.symbol_name()] = model.get_value(v)
            try:
                f = open(f"./out/{os.path.basename(file_name)}/{i}/{i}.pickle", "xb")
            except FileExistsError:
                f = open(f"./out/{os.path.basename(file_name)}/{i}/{i}.pickle", "wb")
            pickle.dump(vars, f)
            f.close()

            try:
                f = open(f"./out/{os.path.basename(file_name)}/{i}/{i}.state", "x")
            except FileExistsError:
                f = open(f"./out/{os.path.basename(file_name)}/{i}/{i}.state", "w")
            if vars:
                print("SYMBOLIC INPUTS:\n", file=f)
                for k, v in vars.items():
                    print(k, '<-', v, file=f)
            print("\nFINAL PROGRAM STATE:\n", file=f)
            display_model(s, s.head_frame().variables, model, f)
            f.close()

def concrete_evaluation(states):
    state = states[0]
    assert all([simplify(v[1]).is_constant() for k, v in state.head_frame().variables.items() if not isinstance(v[1], YouVerifyArray)]), "All variables must be constant."
    return json.dumps({k: simplify(v[1]).constant_value() if not isinstance(v[1], YouVerifyArray) else
                    [simplify(get_model(state.path_cond).get_value(v[1].get_array())).array_value_get(Int(i)).constant_value() for i in range(simplify(v[1].length).constant_value())]
                       for k, v in state.head_frame().variables.items()})

if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog='PROG')
    parser.add_argument('--f', type=str, help='foo help', dest='file')
    parser.add_argument('--input', nargs='?', type=int, help='in help', dest='input')
    args = parser.parse_args(sys.argv[1:])
    display_states_smt2(main(args.file, args.input), args.file, args.input)