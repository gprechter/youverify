from pysmt.shortcuts import get_free_variables, to_smtlib, Solver
from pysmt.fnode import FNode
from ConvertLet import convert

def gen_declare_const(node: FNode):
    const_declarations = []
    already_declared = []
    for const in get_free_variables(node):
        if const.symbol_name() not in already_declared:
            const_declarations.append(f"(declare-const {const.symbol_name()} {const.symbol_type()})")
            already_declared.append(const.symbol_name())
    return const_declarations

def gen_assert(node: FNode):
    with Solver(name="z3", logic="QF_AUFLIA") as s:
        return f"(assert {convert(to_smtlib(node))})"