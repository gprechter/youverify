import sys
import json
from antlr4 import *

from YouVerifyVisitorOld import YouVerifyVisitor
from YouVerifyLexer import YouVerifyLexer
from YouVerifyParser import YouVerifyParser

from pysmt.shortcuts import TRUE, is_sat, simplify, get_model, get_free_variables, Solver
from pysmt.typing import _BoolType
from AST import Program
from State import State, Frame
from SMTLibUtil import *

def main(argv):
    input_stream = FileStream(argv[1])
    lexer = YouVerifyLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = YouVerifyParser(stream)
    variables, functions, statements, labels, records = YouVerifyVisitor().visitProgram(parser.program())
    program = Program(statements, variables, labels, functions)

    for n, v in variables.items():
        if v.name in records:
            variables[n] = records[v.name].elements

    def exec(program):
        states = [State(TRUE(), [Frame(program, 0, variables.copy(), None)])]
        while [state for state in states if not state.is_finished]:
            state = states.pop(0)
            if state.is_finished:
                states.append(state)
                continue
            states.extend([s for s in state.current_statement.exec(state) if is_sat(state.path_cond)])
        return states

    return exec(program)

def simplify_smt(value):
    if isinstance(value, dict):
        return str({k: simplify_smt(v) for k, v in value.items()})
    else:
        return simplify(value)

def display_states_smt2(states):
    for i, state in enumerate(states):
        state_desc = f"{i}\t" + str({k: simplify_smt(v) for k, v in state.head_frame().variables.items()})
        print("" + "=" * len(state_desc) + "")
        print(state_desc)
        print("=" * len(state_desc))
        print("(set-option :produce-models true)")
        print('\n'.join(gen_declare_const(state.path_cond)))
        print(gen_assert(simplify(state.path_cond)))

def concrete_evaluation(states):
    state = states[0]
    assert all([simplify(v).is_constant() for k, v in state.head_frame().variables.items()]), "All variables must be constant."
    return json.dumps({k: simplify(v).constant_value() for k, v in state.head_frame().variables.items()})

if __name__ == '__main__':
    display_states_smt2(main(sys.argv))