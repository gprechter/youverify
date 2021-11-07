import sys
import json
from antlr4 import *

from YouVerifyVisitorOld import YouVerifyVisitor
from YouVerifyLexer import YouVerifyLexer
from YouVerifyParser import YouVerifyParser

from pysmt.shortcuts import TRUE, is_sat, simplify, get_model, get_free_variables, Solver, Int
from pysmt.typing import _BoolType
from AST import Program, Variable, array_to_length_map, YouVerifyArray, ConditionalBranch
from State import State, Frame
from SMTLibUtil import *
from pyeda.inter import *

def main(argv):
    input_stream = FileStream(argv[1])
    lexer = YouVerifyLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = YouVerifyParser(stream)
    variables, functions, statements, labels, records = YouVerifyVisitor().visitProgram(parser.program())
    program = Program(statements, variables, labels, functions)

    State.records = records

    #for stmt in program.statements:
    #    stmt.type_check(program)

    def exec(program):
        state = State(TRUE(), [Frame(program, 0, {k: [v.name, None] for k, v in program.variables.copy().items()}, None)])
        while not state.is_finished:
            state.current_guard = state.get_guard()
            stmt = state.current_statement
            state = stmt.exec(state)
            print(state.value_summaries)
            if not isinstance(stmt, ConditionalBranch):
                state.value_summaries['_pc'].append(state.current_guard)
           # if is_sat(state.path_cond):
                #print(stmt)
        return state

    return exec(program)

def simplify_smt(value, type):
    if isinstance(value, dict):
        return str({k: simplify_smt(v) for k, v in value.items()})
    elif isinstance(value, YouVerifyArray):
        if value.length:
            return f"{[simplify(value.array).array_value_get(Int(i)) for i in range(value.length)]}"
        else:
            return simplify(value.array)
    else:
        return simplify(value[1])

def display_model(state, variables, model, depth = 0):
    for k, v in variables.items():
        if isinstance(v[0], str):
            elems = State.records[v[0]].elements
            if model.get_value(v[1]).constant_value() == 0:
                print(f"{'  ' * depth}{k}: {'null'}")
            else:
                print(f"{'  ' * depth}{k}:")
                display_model(state,
                          {k: [elems[k].name, v] for k, v in state.addr_map[model.get_value(v[1]).constant_value()].items()},
                          model, depth = depth + 1)
        elif isinstance(v[1], YouVerifyArray):
            print(f"{'  ' * depth}{k}: {model.get_value(v[1].array)}")
        else:
            print(f"{'  ' * depth}{k}: {model.get_value(v[1])}")
    #print("MODEL", model)

def display_states_smt2(state):
    for v, vs in state.value_summaries.items():
        if v != '_pc':
            print(v, ', '.join([f"{bdd2expr(g)}: {simplify(val)}" for g, val in vs]))
    print([(k, bdd2expr(v)) if isinstance(v, BinaryDecisionDiagram) else (k, v) for k, v in state.bdd_vars.items()])


def concrete_evaluation(states):
    state = states[0]
    assert all([simplify(v[1]).is_constant() for k, v in state.head_frame().variables.items()]), "All variables must be constant."
    return json.dumps({k: simplify(v[1]).constant_value() for k, v in state.head_frame().variables.items()})

if __name__ == '__main__':
    display_states_smt2(main(sys.argv))