# Generated from YouVerify.g4 by ANTLR 4.9
from antlr4 import *
from AST import *
from State import DefaultState
from Mappings import YVR_SORT_TO_PYSMT, YVR_BINARY_OP_TO_PYSMT, YVR_BOOL_TO_PYSMT, YVR_UNARY_OP_TO_PYSMT, YVR_TERNARY_OP_TO_PYSMT
if __name__ is not None and "." in __name__:
    from .YouVerifyParser import YouVerifyParser
else:
    from YouVerifyParser import YouVerifyParser

from pysmt.shortcuts import Int, ArrayType, BV
from pysmt.typing import BOOL, INT, BVType, _ArrayType


# This class defines a complete generic visitor for a parse tree produced by YouVerifyParser.

class YouVerifyVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by YouVerifyParser#program.
    def visitProgram(self, ctx:YouVerifyParser.ProgramContext):
        variables = dict()
        functions = dict()
        records = dict()

        for decl in ctx.decls:
            type, value = self.visit(decl)
            if type == 'var':
                for val in value:
                    identifier, sort = val
                    variables[identifier] = Variable(sort)
            elif type == 'rec':
                records[value.name] = value
            else:
                name, parameters, local_variables, local_statements, local_labels, return_value = value
                functions[name] = Function(name, parameters, local_variables, local_statements, local_labels, return_value)

        statements = []
        labels = dict()

        for line, stmt in enumerate(ctx.stmts):
            label, stmt = self.visit(stmt)
            if label:
                labels[label] = line
            statements.append(stmt)

        return variables, functions, statements, labels, records

    # Visit a parse tree produced by YouVerifyParser#GLOBAL_VAR.
    def visitGLOBAL_VAR(self, ctx: YouVerifyParser.GLOBAL_VARContext):
        return "var", self.visit(ctx.var)

    # Visit a parse tree produced by YouVerifyParser#GLOBAL_REC.
    def visitGLOBAL_REC(self, ctx: YouVerifyParser.GLOBAL_RECContext):
        return "rec", self.visit(ctx.rec)

    # Visit a parse tree produced by YouVerifyParser#GLOBAL_FUNC.
    def visitGLOBAL_FUNC(self, ctx: YouVerifyParser.GLOBAL_FUNCContext):
        return "func", self.visit(ctx.func)

    # Visit a parse tree produced by YouVerifyParser#record.
    def visitRecord(self, ctx: YouVerifyParser.RecordContext):
        elements = [(identifier, sort) for identifier, sort in sum([self.visit(p) for p in ctx.elems], [])]
        return Record(ctx.name.text, [e[0] for e in elements], [e[1] for e in elements])

    # Visit a parse tree produced by YouVerifyParser#ALLOC_CONC.
    def visitALLOC_CONC(self, ctx: YouVerifyParser.ALLOC_CONCContext):
        return Alloc_Concrete(self.visit(ctx.target), ctx.operator.text, [self.visit(e) for e in ctx.operands])

    # Visit a parse tree produced by YouVerifyParser#ALLOC_SYMB.
    def visitALLOC_SYMB(self, ctx: YouVerifyParser.ALLOC_SYMBContext):
        return Alloc_Symbolic(self.visit(ctx.target), ctx.identifier.text)


    # Visit a parse tree produced by YouVerifyParser#function.
    def visitFunction(self, ctx: YouVerifyParser.FunctionContext):
        parameters = {identifier: Variable(sort) for identifier, sort in sum([self.visit(p) for p in ctx.params], [])}
        variables = {identifier: Variable(sort) for identifier, sort in sum([self.visit(p) for p in ctx.decls], [])}

        statements = list()
        labels = dict()
        for line, stmt in enumerate(ctx.stmts):
            label, stmt = self.visit(stmt)
            if label:
                labels[label] = line
            statements.append(stmt)

        return ctx.name.text, parameters, variables, statements, labels, self.visit(ctx.return_type) if ctx.return_type else None

    # Visit a parse tree produced by YouVerifyParser#RETURN.
    def visitRETURN(self, ctx: YouVerifyParser.RETURNContext):
        return Return(self.visit(ctx.expression))

    # Visit a parse tree produced by YouVerifyParser#RETURN_NO_VALUE.
    def visitRETURN_NO_VALUE(self, ctx:YouVerifyParser.RETURN_NO_VALUEContext):
        return Return(None)

    # Visit a parse tree produced by YouVerifyParser#FUNC_CALL.
    def visitFUNC_CALL(self, ctx: YouVerifyParser.FUNC_CALLContext):
        return FunctionCallAndAssignment(self.visit(ctx.target), ctx.operator.text, [self.visit(e) for e in ctx.operands])

    # Visit a parse tree produced by YouVerifyParser#FUNC_CALL_NO_VALUE.
    def visitFUNC_CALL_NO_VALUE(self, ctx: YouVerifyParser.FUNC_CALL_NO_VALUEContext):
        return FunctionCallWithNoAssignment(ctx.operator.text, [self.visit(e) for e in ctx.operands])

    # Visit a parse tree produced by YouVerifyParser#ASSERT.
    def visitASSERT(self, ctx: YouVerifyParser.ASSERTContext):
        return

    # Visit a parse tree produced by YouVerifyParser#ASSUME.
    def visitASSUME(self, ctx: YouVerifyParser.ASSUMEContext):
        return Assume(self.visit(ctx.expression))

    # Visit a parse tree produced by YouVerifyParser#expr.
    def visitExpr(self, ctx: YouVerifyParser.ExprContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by YouVerifyParser#ASSERT.
    def visitASSERT(self, ctx: YouVerifyParser.ASSERTContext):
        return Assert(self.visit(ctx.expression))

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

    # Visit a parse tree produced by YouVerifyParser#ASSIGN_TARGET_RECORD_INDEX.
    def visitASSIGN_TARGET_RECORD_INDEX(self, ctx: YouVerifyParser.ASSIGN_TARGET_RECORD_INDEXContext):
        return self.visit(ctx.expression)

    # Visit a parse tree produced by YouVerifyParser#ASSIGN_TARGET_ARRAY_INDEX.
    def visitASSIGN_TARGET_ARRAY_INDEX(self, ctx: YouVerifyParser.ASSIGN_TARGET_ARRAY_INDEXContext):
        return self.visit(ctx.expression)

    # Visit a parse tree produced by YouVerifyParser#ASSIGN_TARGET_PTR_DEREF.
    def visitASSIGN_TARGET_PTR_DEREF(self, ctx:YouVerifyParser.ASSIGN_TARGET_PTR_DEREFContext):
        return self.visit(ctx.expression)

    # Visit a parse tree produced by YouVerifyParser#CONDITIONAL_BRANCH.
    def visitCONDITIONAL_BRANCH(self, ctx: YouVerifyParser.CONDITIONAL_BRANCHContext):
        return ConditionalBranch(self.visit(ctx.expression), ctx.label.text)

    # Visit a parse tree produced by YouVerifyParser#UNCONDITIONAL_BRANCH.
    def visitUNCONDITIONAL_BRANCH(self, ctx: YouVerifyParser.UNCONDITIONAL_BRANCHContext):
        return UnconditionalBranch(ctx.label.text)

    # Visit a parse tree produced by YouVerifyParser#decl.
    def visitDecl(self, ctx:YouVerifyParser.DeclContext):
        return [(id.text, self.visit(ctx.s)) for id in ctx.identifiers]

    # Visit a parse tree produced by YouVerifyParser#ptr_deref_expr.
    def visitPtr_deref_expr(self, ctx:YouVerifyParser.Ptr_deref_exprContext):
        return Pointer_Dereference_Expression(ctx.identifier.text)

    # Visit a parse tree produced by YouVerifyParser#atomic_expr.
    def visitSIMPLE(self, ctx: YouVerifyParser.SIMPLEContext):
        if ctx.BOOLEAN():
            return Value(YVR_BOOL_TO_PYSMT[ctx.atom.text], BOOL)
        elif ctx.INTEGER():
            return Value(Int(int(ctx.atom.text)), INT)
        elif ctx.IDENTIFIER():
            if ctx.atom.text.lower() == 'null':
                return NULL()
            else:
                return Variable(ctx.atom.text)


    # Visit a parse tree produced by YouVerifyParser#ARRAY.
    def visitARRAY(self, ctx:YouVerifyParser.ARRAYContext):
        return NewArrayExpression(default=self.visit(ctx.expression))

    # Visit a parse tree produced by YouVerifyParser#FIXED_SIZE_ARRAY.
    def visitFIXED_SIZE_ARRAY(self, ctx: YouVerifyParser.FIXED_SIZE_ARRAYContext):
        return NewArrayExpression(default=self.visit(ctx.expression), length=int(ctx.length.text))

    # Visit a parse tree produced by YouVerifyParser#BIT_VECTOR.
    def visitBIT_VECTOR(self, ctx:YouVerifyParser.BIT_VECTORContext):
        return Value(BV(int(ctx.value.text), int(ctx.size.text)), BVType(int(ctx.size.text)))

    # Visit a parse tree produced by YouVerifyParser#SYMBOL.
    def visitSYMBOL(self, ctx: YouVerifyParser.SYMBOLContext):
        return UniqueSymbol(self.visit(ctx.s))

    # Visit a parse tree produced by YouVerifyParser#NAMED_SYMBOL.
    def visitNAMED_SYMBOL(self, ctx: YouVerifyParser.NAMED_SYMBOLContext):
        sort = self.visit(ctx.s)
        if isinstance(sort, _ArrayType):
            length = FreshSymbol(INT)
            if length.symbol_name() in DefaultState.inputs:
                length = DefaultState.inputs[length.symbol_name()]
            array = Symbol(ctx.identifier.text, sort)
            if array.symbol_name() in DefaultState.inputs:
                array = DefaultState.inputs[array.symbol_name()]

            return Value(YouVerifyArray(0, length=length, array=[array]), sort)
        sym = Symbol(ctx.identifier.text, sort)
        if sym.symbol_name() in DefaultState.inputs:
            sym = DefaultState.inputs[sym.symbol_name()]
        return Value(sym, sort)

    # Visit a parse tree produced by YouVerifyParser#UNARY.
    def visitUNARY(self, ctx:YouVerifyParser.UNARYContext):
        return UnaryExpression(YVR_UNARY_OP_TO_PYSMT[ctx.op.text], ctx.op.text, self.visit(ctx.e))

    # Visit a parse tree produced by YouVerifyParser#BINARY.
    def visitBINARY(self, ctx:YouVerifyParser.BINARYContext):
        return BinaryExpression(self.visit(ctx.lhs), YVR_BINARY_OP_TO_PYSMT[ctx.op.text], ctx.op.text, self.visit(ctx.rhs))

    # Visit a parse tree produced by YouVerifyParser#TERNARY.
    def visitTERNARY(self, ctx: YouVerifyParser.TERNARYContext):
        return TernaryExpression(YVR_TERNARY_OP_TO_PYSMT[ctx.op.text], self.visit(ctx.first), self.visit(ctx.second), self.visit(ctx.third))

    # Visit a parse tree produced by YouVerifyParser#RECORD_INDEX.
    def visitRECORD_INDEX(self, ctx: YouVerifyParser.RECORD_INDEXContext):
        return RecordIndexExpression(ctx.rec.text, ctx.item.text)

    # Visit a parse tree produced by YouVerifyParser#array_index_expr.
    def visitARRAY_INDEX(self, ctx: YouVerifyParser.ARRAY_INDEXContext):
        return ArrayIndexExpression(Variable(ctx.array.text), self.visit(ctx.index))

    # Visit a parse tree produced by YouVerifyParser#PTR_SORT.
    def visitPTR_SORT(self, ctx: YouVerifyParser.PTR_SORTContext):
        contained = self.visitSimple_sort(ctx.s)
        return YVR_SORT_TO_PYSMT['ARRAY'](INT, BVType(32) if isinstance(contained, str) else contained)

    # Visit a parse tree produced by YouVerifyParser#SIMPLE_SORT.
    def visitSIMPLE_SORT(self, ctx: YouVerifyParser.SIMPLE_SORTContext):
        return self.visitChildren(ctx)

    # Visit a parse tree produced by YouVerifyParser#simple_sort.
    def visitSimple_sort(self, ctx: YouVerifyParser.Simple_sortContext):
        outer_sort = ctx.s.text
        if outer_sort == 'ARRAY':
            contained = self.visit(ctx.contained_sort)
            return YVR_SORT_TO_PYSMT[outer_sort](INT, BVType(32) if isinstance(contained, str) else contained)
        elif outer_sort == 'BV':
            return YVR_SORT_TO_PYSMT[outer_sort](int(ctx.size.text))
        elif outer_sort in YVR_SORT_TO_PYSMT:
            return YVR_SORT_TO_PYSMT[outer_sort]
        else:
            return outer_sort

    # Visit a parse tree produced by YouVerifyParser#REPORT.
    def visitREPORT(self, ctx: YouVerifyParser.REPORTContext):
        return Report(ctx.identifier.text)

del YouVerifyParser
