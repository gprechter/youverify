# Generated from SMTLibLisp.g4 by ANTLR 4.9
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .SMTLibLispParser import SMTLibLispParser
else:
    from SMTLibLispParser import SMTLibLispParser

# This class defines a complete generic visitor for a parse tree produced by SMTLibLispParser.

class SMTLibLispVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by SMTLibLispParser#expression.
    def visitExpression(self, ctx:SMTLibLispParser.ExpressionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by SMTLibLispParser#collection.
    def visitCollection(self, ctx:SMTLibLispParser.CollectionContext):
        return [self.visit(e) for e in ctx.expressions]


    # Visit a parse tree produced by SMTLibLispParser#atom.
    def visitAtom(self, ctx:SMTLibLispParser.AtomContext):
        return ctx.value.text



del SMTLibLispParser