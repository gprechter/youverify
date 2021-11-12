from copy import copy, deepcopy


from pyeda.inter import *
from pysmt.shortcuts import TRUE, FALSE, And, Not, Or, Store, simplify, is_sat, Int

class Frame:
    def __init__(self, function, pc, variables, return_target):
        self.function = function
        self.pc = pc
        self.variables = variables
        self.return_target = return_target

    def __copy__(self):
        return Frame(self.function, self.pc, deepcopy(self.variables), self.return_target)

class PathConstraint:
    bdd_vars = {}
    num_vars = 0
    def __init__(self):
        fake = bddvar('fake')
        self.bdd = fake.restrict({fake: 1})
        self.pc = TRUE()

    def __copy__(self):
        new = PathConstraint()
        new.bdd = self.bdd
        new.pc = self.pc
        return new

    def apply_AND(self, other):
        new = PathConstraint()
        new.bdd = self.bdd & other.bdd
        new.pc = And(self.pc, other.pc)
        return new

    def apply_OR(self, other):
        new = PathConstraint()
        new.bdd = self.bdd | other.bdd
        new.pc = Or(self.pc, other.pc)
        return new

    def apply_NOT(self):
        new = PathConstraint()
        new.bdd = ~self.bdd
        new.pc = Not(self.pc)
        return new

    def is_zero(self):
        return self.bdd.is_zero()

    def is_unsat(self):
        return not is_sat(self.pc)

    def from_condition(self, cond):
        if cond not in PathConstraint.bdd_vars:
            PathConstraint.bdd_vars[cond] = bddvar('c', PathConstraint.num_vars)
            PathConstraint.num_vars += 1
        new = PathConstraint()
        new.bdd = PathConstraint.bdd_vars[cond]
        new.pc = cond
        return new

    def __repr__(self):
        return f"{simplify(self.pc)}"

class State:
    records = {}
    bdd_vars = {}
    num_vars = 0
    def __init__(self, path_cond, frame_stack, base_addr = 1, addr_map = {0: None}, conc_sym_pointers = {}):
        self.path_cond = path_cond
        self.frame_stack = frame_stack
        self.base_addr = base_addr
        self.addr_map = addr_map
        self.concrete_symbolic_pointers = conc_sym_pointers
        self.value_summaries = {'_pc': [[PathConstraint(), 0]]}
        self.value_summaries.update({k: [[PathConstraint(), Int(0)]] for k in self.head_frame().variables})
        print(self.value_summaries)

    def __copy__(self):
        return State(self.path_cond, [copy(f) for f in self.frame_stack], self.base_addr, deepcopy(self.addr_map), deepcopy(self.concrete_symbolic_pointers))

    def assign_variable(self, var, val):
        merge = {}
        old_vs = [[self.current_guard[0].apply_NOT().apply_AND(g), v] for g, v in self.value_summaries[var]]
        new_vs = [[self.current_guard[0].apply_AND(g), v] for g, v in val]
        for g, v in old_vs + new_vs:
            if not g.is_zero() and not g.is_unsat():
                if v not in merge:
                    merge[v] = g
                else:
                    merge[v] = merge[v].apply_OR(g)
        self.value_summaries[var] = [[v, k] for k, v in merge.items()]

    def get_variable(self, var):
        return self.value_summaries[var]

    def get_variable_type(self, var):
        if var in self.head_frame().variables:
            return self.head_frame().variables[var][0]
        else:
            return self.frame_stack[0].variables[var][0]
    def split(self, cond, pc, unconditional=False):
        new_g = PathConstraint().apply_NOT()
        for g, v in cond:
            new_g = new_g.apply_OR(g.apply_AND(PathConstraint().from_condition(v)))
        if not (self.current_guard[0].apply_AND(new_g).is_zero() or self.current_guard[0].apply_AND(new_g).is_unsat()):
            self.value_summaries['_pc'].append([self.current_guard[0].apply_AND(new_g), pc])
        if not (self.current_guard[0].apply_AND(new_g.apply_NOT()).is_zero() or self.current_guard[0].apply_AND(new_g.apply_NOT()).is_unsat()):
            self.value_summaries['_pc'].append([self.current_guard[0].apply_AND(new_g.apply_NOT()), self.current_guard[1] + 1])
        return self

    def advance_pc(self):
        self.current_guard = [self.current_guard[0], self.current_guard[1] + 1]
        return self

    def update_pc(self, pc):
        self.head_frame().pc = pc
        return self

    @property
    def pc(self):
        return self.current_guard[1]

    @property
    def current_statement(self):
        return self.head_frame().function.statements[self.pc]

    def head_frame(self):
        return self.frame_stack[-1]

    def push_frame(self, frame):
        self.frame_stack.append(frame)

    def pop_frame(self, return_value):
        target = self.frame_stack.pop().return_target
        if target is not None and return_value is not None:
            target(self, return_value)

    def get_guard(self):
        for i in range(len(self.value_summaries['_pc'])):
            if self.value_summaries['_pc'][i][1] < len(self.head_frame().function.statements):
                return self.value_summaries['_pc'].pop(i)

    @property
    def is_finished(self):
        return (len(self.frame_stack) == 1) and all(pc[1] >= len(self.head_frame().function.statements) for pc in self.value_summaries['_pc'])