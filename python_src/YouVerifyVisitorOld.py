# Generated from YouVerify.g4 by ANTLR 4.9
from antlr4 import *
from AST import *
from Mappings import YVR_SORT_TO_PYSMT, YVR_OP_TO_PYSMT, YVR_BOOL_TO_PYSMT
if __name__ is not None and "." in __name__:
    from .YouVerifyParser import YouVerifyParser
else:
    from YouVerifyParser import YouVerifyParser

from pysmt.shortcuts import Int, ArrayType

# This class defines a complete generic visitor for a parse tree produced by YouVerifyParser.

class YouVerifyVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by YouVerifyParser#program.
    def visitProgram(self, ctx:YouVerifyParser.ProgramContext):
        variables = dict()

        for decl in ctx.decls:
            identifier, sort = self.visitDecl(decl)
            variables[identifier] = Variable(decl.sort)

        statements = []
        labels = dict()

        for line, stmt in enumerate(ctx.stmts):
            label, stmt = self.visit(stmt)
            if label:
                labels[label] = line
            statements.append(stmt)

        return variables, statements, labels

    # Visit a parse tree produced by YouVerifyParser#LABELED.
    def visitLABELED(self, ctx: YouVerifyParser.LABELEDContext):
        return ctx.identifier.text, self.visit(ctx.statement)

    # Visit a parse tree produced by YouVerifyParser#UNLABELED.
    def visitUNLABELED(self, ctx: YouVerifyParser.UNLABELEDContext):
        return None, self.visit(ctx.statement)

    # Visit a parse tree produced by YouVerifyParser#ASSIGN.
    def visitASSIGN(self, ctx:YouVerifyParser.ASSIGNContext):
        return Assignment(self.visit(ctx.target), self.visit(ctx.expression))

    # Visit a parse tree produced by YouVerifyParser#ASSIGN_TARGET_IDENTIFIER.
    def visitASSIGN_TARGET_IDENTIFIER(self, ctx: YouVerifyParser.ASSIGN_TARGET_IDENTIFIERContext):
        return Variable(ctx.identifier.text)

    # Visit a parse tree produced by YouVerifyParser#ASSIGN_TARGET_ARRAY_INDEX.
    def visitASSIGN_TARGET_ARRAY_INDEX(self, ctx: YouVerifyParser.ASSIGN_TARGET_ARRAY_INDEXContext):
        return self.visit(ctx.expression)

    # Visit a parse tree produced by YouVerifyParser#CONDITIONAL_BRANCH.
    def visitCONDITIONAL_BRANCH(self, ctx: YouVerifyParser.CONDITIONAL_BRANCHContext):
        return ConditionalBranch(self.visit(ctx.expression), ctx.label.text)

    # Visit a parse tree produced by YouVerifyParser#UNCONDITIONAL_BRANCH.
    def visitUNCONDITIONAL_BRANCH(self, ctx: YouVerifyParser.UNCONDITIONAL_BRANCHContext):
        return UnconditionalBranch(ctx.label.text)

    # Visit a parse tree produced by YouVerifyParser#decl.
    def visitDecl(self, ctx:YouVerifyParser.DeclContext):
        return ctx.identifier.text, self.visit(ctx.s)


    # Visit a parse tree produced by YouVerifyParser#ATOMIC.
    def visitATOMIC(self, ctx:YouVerifyParser.ATOMICContext):
        if ctx.BOOLEAN():
            return Value(YVR_BOOL_TO_PYSMT[ctx.atom.text])
        elif ctx.INTEGER():
            return Value(Int(int(ctx.atom.text)))
        elif ctx.IDENTIFIER():
            return Variable(ctx.atom.text)

    # Visit a parse tree produced by YouVerifyParser#ARRAY.
    def visitARRAY(self, ctx:YouVerifyParser.ARRAYContext):
        return NewArrayExpression(default=self.visit(ctx.expression))

    # Visit a parse tree produced by YouVerifyParser#SYMBOL.
    def visitSYMBOL(self, ctx: YouVerifyParser.SYMBOLContext):
        return UniqueSymbol(self.visit(ctx.s))

    # Visit a parse tree produced by YouVerifyParser#NAMED_SYMBOL.
    def visitNAMED_SYMBOL(self, ctx: YouVerifyParser.NAMED_SYMBOLContext):
        return Value(Symbol(ctx.identifier.text, self.visit(ctx.s)))

    # Visit a parse tree produced by YouVerifyParser#BINARY.
    def visitBINARY(self, ctx:YouVerifyParser.BINARYContext):
        return BinaryExpression(self.visit(ctx.lhs), YVR_OP_TO_PYSMT[ctx.op.text], self.visit(ctx.rhs))

    # Visit a parse tree produced by YouVerifyParser#array_index_expr.
    def visitArray_index_expr(self, ctx: YouVerifyParser.Array_index_exprContext):
        return ArrayIndexExpression(Variable(ctx.array.text), self.visit(ctx.index))

    # Visit a parse tree produced by YouVerifyParser#sort.
    def visitSort(self, ctx: YouVerifyParser.SortContext):
        if ctx.contained_sort:
            return YVR_SORT_TO_PYSMT[ctx.s.text](INT, self.visit(ctx.contained_sort))
        else:
            return YVR_SORT_TO_PYSMT[ctx.s.text]


del YouVerifyParser