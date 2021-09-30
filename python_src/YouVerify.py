import sys
import json
from antlr4 import *

from YouVerifyVisitorOld import YouVerifyVisitor
from YouVerifyLexer import YouVerifyLexer
from YouVerifyParser import YouVerifyParser

from pysmt.shortcuts import TRUE, is_sat, simplify, get_model, get_free_variables, Solver
from pysmt.typing import _BoolType
from AST import Program
from State import State
from SMTLibUtil import *
def main(argv):
    input_stream = FileStream(argv[1])
    lexer = YouVerifyLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = YouVerifyParser(stream)
    variables, functions, statements, labels = YouVerifyVisitor().visitProgram(parser.program())
    program = Program(statements, variables, labels)
    Program.variables = variables


    def exec(program):
        states = [State(program)]
        while [state for state in states if state.pc < len(program.statements)]:
            state = states.pop(0)
            if state.pc >= len(program.statements):
                states.append(state)
                continue
            states.extend([s for s in program.statements[state.pc].exec(state) if is_sat(state.path_cond)])
        return states

    return exec(program)

def display_states_smt2(states):
    for i, state in enumerate(states):
        state_desc = f"{i}\t" + str({k: simplify(v) for k, v in state.variables.items()})
        print("=" * len(state_desc))
        print(state_desc)
        print("=" * len(state_desc))
        print("(set-option :produce-models true)")
        print('\n'.join(gen_declare_const(state.path_cond)))
        print(gen_assert(simplify(state.path_cond)))

def concrete_evaluation(states):
    state = states[0]
    assert all([simplify(v).is_constant() for k, v in state.variables.items()]), "All variables must be constant."
    return json.dumps({k: simplify(v).constant_value() for k, v in state.variables.items()})

if __name__ == '__main__':
    display_states_smt2(main(sys.argv))