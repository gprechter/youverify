import sys

from antlr4 import InputStream, CommonTokenStream

from SMTLibLispLexer import SMTLibLispLexer
from SMTLibLispParser import SMTLibLispParser
from SMTLibLispVisitor import SMTLibLispVisitor


def convert(str):
    input_stream = InputStream(str)
    lexer = SMTLibLispLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = SMTLibLispParser(stream)
    return convert_let(SMTLibLispVisitor().visitExpression(parser.expression()), {})

def convert_let(expr, definitions):
    if isinstance(expr, list):
        if expr[0] == 'let':
            definitions = definitions.copy()
            for definition in expr[1]:
                definitions[definition[0]] = convert_let(definition[1], definitions)
            return convert_let(expr[2], definitions)
        else:
            return f"({' '.join([convert_let(e, definitions) for e in expr])})"
    else:
        if expr in definitions:
            return definitions[expr]
        else:
            return expr