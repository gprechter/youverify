# Generated from YouVerify.g4 by ANTLR 4.9
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .YouVerifyParser import YouVerifyParser
else:
    from YouVerifyParser import YouVerifyParser

# This class defines a complete generic visitor for a parse tree produced by YouVerifyParser.

class YouVerifyVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by YouVerifyParser#program.
    def visitProgram(self, ctx:YouVerifyParser.ProgramContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#GLOBAL_VAR.
    def visitGLOBAL_VAR(self, ctx:YouVerifyParser.GLOBAL_VARContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#GLOBAL_REC.
    def visitGLOBAL_REC(self, ctx:YouVerifyParser.GLOBAL_RECContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#GLOBAL_FUNC.
    def visitGLOBAL_FUNC(self, ctx:YouVerifyParser.GLOBAL_FUNCContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#function.
    def visitFunction(self, ctx:YouVerifyParser.FunctionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#record.
    def visitRecord(self, ctx:YouVerifyParser.RecordContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#LABELED.
    def visitLABELED(self, ctx:YouVerifyParser.LABELEDContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#UNLABELED.
    def visitUNLABELED(self, ctx:YouVerifyParser.UNLABELEDContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#RETURN.
    def visitRETURN(self, ctx:YouVerifyParser.RETURNContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#RETURN_NO_VALUE.
    def visitRETURN_NO_VALUE(self, ctx:YouVerifyParser.RETURN_NO_VALUEContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#ASSERT.
    def visitASSERT(self, ctx:YouVerifyParser.ASSERTContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#ASSIGN.
    def visitASSIGN(self, ctx:YouVerifyParser.ASSIGNContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#FUNC_CALL.
    def visitFUNC_CALL(self, ctx:YouVerifyParser.FUNC_CALLContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#FUNC_CALL_NO_VALUE.
    def visitFUNC_CALL_NO_VALUE(self, ctx:YouVerifyParser.FUNC_CALL_NO_VALUEContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#ALLOC_CONC.
    def visitALLOC_CONC(self, ctx:YouVerifyParser.ALLOC_CONCContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#ALLOC_SYMB.
    def visitALLOC_SYMB(self, ctx:YouVerifyParser.ALLOC_SYMBContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#CONDITIONAL_BRANCH.
    def visitCONDITIONAL_BRANCH(self, ctx:YouVerifyParser.CONDITIONAL_BRANCHContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#UNCONDITIONAL_BRANCH.
    def visitUNCONDITIONAL_BRANCH(self, ctx:YouVerifyParser.UNCONDITIONAL_BRANCHContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#ASSIGN_TARGET_IDENTIFIER.
    def visitASSIGN_TARGET_IDENTIFIER(self, ctx:YouVerifyParser.ASSIGN_TARGET_IDENTIFIERContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#ASSIGN_TARGET_RECORD_INDEX.
    def visitASSIGN_TARGET_RECORD_INDEX(self, ctx:YouVerifyParser.ASSIGN_TARGET_RECORD_INDEXContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#ASSIGN_TARGET_ARRAY_INDEX.
    def visitASSIGN_TARGET_ARRAY_INDEX(self, ctx:YouVerifyParser.ASSIGN_TARGET_ARRAY_INDEXContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#decl.
    def visitDecl(self, ctx:YouVerifyParser.DeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#ARRAY.
    def visitARRAY(self, ctx:YouVerifyParser.ARRAYContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#ARRAY_INDEX.
    def visitARRAY_INDEX(self, ctx:YouVerifyParser.ARRAY_INDEXContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#ATOMIC.
    def visitATOMIC(self, ctx:YouVerifyParser.ATOMICContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#FIXED_SIZE_ARRAY.
    def visitFIXED_SIZE_ARRAY(self, ctx:YouVerifyParser.FIXED_SIZE_ARRAYContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#SYMBOL.
    def visitSYMBOL(self, ctx:YouVerifyParser.SYMBOLContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#BIT_VECTOR.
    def visitBIT_VECTOR(self, ctx:YouVerifyParser.BIT_VECTORContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#BINARY.
    def visitBINARY(self, ctx:YouVerifyParser.BINARYContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#NAMED_SYMBOL.
    def visitNAMED_SYMBOL(self, ctx:YouVerifyParser.NAMED_SYMBOLContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#TERNARY.
    def visitTERNARY(self, ctx:YouVerifyParser.TERNARYContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#RECORD_INDEX.
    def visitRECORD_INDEX(self, ctx:YouVerifyParser.RECORD_INDEXContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#UNARY.
    def visitUNARY(self, ctx:YouVerifyParser.UNARYContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#array_index_expr.
    def visitArray_index_expr(self, ctx:YouVerifyParser.Array_index_exprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by YouVerifyParser#sort.
    def visitSort(self, ctx:YouVerifyParser.SortContext):
        return self.visitChildren(ctx)



del YouVerifyParser