# Generated from SMTLibLisp.g4 by ANTLR 4.9
# encoding: utf-8
from antlr4 import *
from io import StringIO
import sys
if sys.version_info[1] > 5:
	from typing import TextIO
else:
	from typing.io import TextIO


def serializedATN():
    with StringIO() as buf:
        buf.write("\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\6")
        buf.write("\27\4\2\t\2\4\3\t\3\4\4\t\4\3\2\3\2\5\2\13\n\2\3\3\3\3")
        buf.write("\6\3\17\n\3\r\3\16\3\20\3\3\3\3\3\4\3\4\3\4\2\2\5\2\4")
        buf.write("\6\2\2\2\25\2\n\3\2\2\2\4\f\3\2\2\2\6\24\3\2\2\2\b\13")
        buf.write("\5\4\3\2\t\13\5\6\4\2\n\b\3\2\2\2\n\t\3\2\2\2\13\3\3\2")
        buf.write("\2\2\f\16\7\3\2\2\r\17\5\2\2\2\16\r\3\2\2\2\17\20\3\2")
        buf.write("\2\2\20\16\3\2\2\2\20\21\3\2\2\2\21\22\3\2\2\2\22\23\7")
        buf.write("\4\2\2\23\5\3\2\2\2\24\25\7\6\2\2\25\7\3\2\2\2\4\n\20")
        return buf.getvalue()


class SMTLibLispParser ( Parser ):

    grammarFileName = "SMTLibLisp.g4"

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    sharedContextCache = PredictionContextCache()

    literalNames = [ "<INVALID>", "'('", "')'", "' '" ]

    symbolicNames = [ "<INVALID>", "OPAREN", "CPAREN", "WHITESPACE", "VALUE" ]

    RULE_expression = 0
    RULE_collection = 1
    RULE_atom = 2

    ruleNames =  [ "expression", "collection", "atom" ]

    EOF = Token.EOF
    OPAREN=1
    CPAREN=2
    WHITESPACE=3
    VALUE=4

    def __init__(self, input:TokenStream, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.9")
        self._interp = ParserATNSimulator(self, self.atn, self.decisionsToDFA, self.sharedContextCache)
        self._predicates = None




    class ExpressionContext(ParserRuleContext):

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def collection(self):
            return self.getTypedRuleContext(SMTLibLispParser.CollectionContext,0)


        def atom(self):
            return self.getTypedRuleContext(SMTLibLispParser.AtomContext,0)


        def getRuleIndex(self):
            return SMTLibLispParser.RULE_expression

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitExpression" ):
                return visitor.visitExpression(self)
            else:
                return visitor.visitChildren(self)




    def expression(self):

        localctx = SMTLibLispParser.ExpressionContext(self, self._ctx, self.state)
        self.enterRule(localctx, 0, self.RULE_expression)
        try:
            self.state = 8
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [SMTLibLispParser.OPAREN]:
                self.enterOuterAlt(localctx, 1)
                self.state = 6
                self.collection()
                pass
            elif token in [SMTLibLispParser.VALUE]:
                self.enterOuterAlt(localctx, 2)
                self.state = 7
                self.atom()
                pass
            else:
                raise NoViableAltException(self)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class CollectionContext(ParserRuleContext):

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser
            self._expression = None # ExpressionContext
            self.expressions = list() # of ExpressionContexts

        def OPAREN(self):
            return self.getToken(SMTLibLispParser.OPAREN, 0)

        def CPAREN(self):
            return self.getToken(SMTLibLispParser.CPAREN, 0)

        def expression(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(SMTLibLispParser.ExpressionContext)
            else:
                return self.getTypedRuleContext(SMTLibLispParser.ExpressionContext,i)


        def getRuleIndex(self):
            return SMTLibLispParser.RULE_collection

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitCollection" ):
                return visitor.visitCollection(self)
            else:
                return visitor.visitChildren(self)




    def collection(self):

        localctx = SMTLibLispParser.CollectionContext(self, self._ctx, self.state)
        self.enterRule(localctx, 2, self.RULE_collection)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 10
            self.match(SMTLibLispParser.OPAREN)
            self.state = 12 
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while True:
                self.state = 11
                localctx._expression = self.expression()
                localctx.expressions.append(localctx._expression)
                self.state = 14 
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                if not (_la==SMTLibLispParser.OPAREN or _la==SMTLibLispParser.VALUE):
                    break

            self.state = 16
            self.match(SMTLibLispParser.CPAREN)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class AtomContext(ParserRuleContext):

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser
            self.value = None # Token

        def VALUE(self):
            return self.getToken(SMTLibLispParser.VALUE, 0)

        def getRuleIndex(self):
            return SMTLibLispParser.RULE_atom

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitAtom" ):
                return visitor.visitAtom(self)
            else:
                return visitor.visitChildren(self)




    def atom(self):

        localctx = SMTLibLispParser.AtomContext(self, self._ctx, self.state)
        self.enterRule(localctx, 4, self.RULE_atom)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 18
            localctx.value = self.match(SMTLibLispParser.VALUE)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx





