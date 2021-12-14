# Generated from SMTLibLisp.g4 by ANTLR 4.9
from antlr4 import *
from io import StringIO
from typing.io import TextIO
import sys



def serializedATN():
    with StringIO() as buf:
        buf.write("\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\6")
        buf.write("\34\b\1\4\2\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\3\2\3")
        buf.write("\2\3\3\3\3\3\4\3\4\3\4\3\4\3\5\3\5\3\6\6\6\31\n\6\r\6")
        buf.write("\16\6\32\2\2\7\3\3\5\4\7\5\t\2\13\6\3\2\3\6\2\13\13\"")
        buf.write("\"*+^^\2\33\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\13\3")
        buf.write("\2\2\2\3\r\3\2\2\2\5\17\3\2\2\2\7\21\3\2\2\2\t\25\3\2")
        buf.write("\2\2\13\30\3\2\2\2\r\16\7*\2\2\16\4\3\2\2\2\17\20\7+\2")
        buf.write("\2\20\6\3\2\2\2\21\22\7\"\2\2\22\23\3\2\2\2\23\24\b\4")
        buf.write("\2\2\24\b\3\2\2\2\25\26\n\2\2\2\26\n\3\2\2\2\27\31\5\t")
        buf.write("\5\2\30\27\3\2\2\2\31\32\3\2\2\2\32\30\3\2\2\2\32\33\3")
        buf.write("\2\2\2\33\f\3\2\2\2\4\2\32\3\b\2\2")
        return buf.getvalue()


class SMTLibLispLexer(Lexer):

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    OPAREN = 1
    CPAREN = 2
    WHITESPACE = 3
    VALUE = 4

    channelNames = [ u"DEFAULT_TOKEN_CHANNEL", u"HIDDEN" ]

    modeNames = [ "DEFAULT_MODE" ]

    literalNames = [ "<INVALID>",
            "'('", "')'", "' '" ]

    symbolicNames = [ "<INVALID>",
            "OPAREN", "CPAREN", "WHITESPACE", "VALUE" ]

    ruleNames = [ "OPAREN", "CPAREN", "WHITESPACE", "CHAR_NO_NL", "VALUE" ]

    grammarFileName = "SMTLibLisp.g4"

    def __init__(self, input=None, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.9")
        self._interp = LexerATNSimulator(self, self.atn, self.decisionsToDFA, PredictionContextCache())
        self._actions = None
        self._predicates = None


