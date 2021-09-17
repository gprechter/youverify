import sys
from antlr4 import *

from YouVerifyVisitorOld import YouVerifyVisitor
from YouVerifyLexer import YouVerifyLexer
from YouVerifyParser import YouVerifyParser

from pysmt.shortcuts import TRUE, is_sat, simplify
from AST import Program
from State import State
def main(argv):
    input_stream = FileStream(argv[1])
    lexer = YouVerifyLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = YouVerifyParser(stream)
    variables, statements, labels = YouVerifyVisitor().visitProgram(parser.program())

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
        for state in states:
            print(simplify(state.path_cond))
            print({k: simplify(v) for k, v in state.variables.items()})

    exec(program)


if __name__ == '__main__':
    main(sys.argv)