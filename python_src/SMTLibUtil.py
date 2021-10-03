from pysmt.shortcuts import get_free_variables, to_smtlib, Solver
from pysmt.fnode import FNode
from ConvertLet import convert

def gen_declare_const(node: FNode):
    const_declarations = []
    for const in get_free_variables(node):
        const_declarations.append(f"(declare-const {const.symbol_name()} {const.symbol_type()})")
    return const_declarations

def gen_assert(node: FNode):
    with Solver(name="z3", logic="QF_AUFLIA") as s:
        return f"(assert {convert(to_smtlib(node))})"