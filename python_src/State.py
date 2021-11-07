from copy import copy, deepcopy

from pysmt.shortcuts import TRUE, FALSE, And, Not, Store
from pyeda.inter import *

class Frame:
    def __init__(self, function, pc, variables, return_target):
        self.function = function
        self.pc = pc
        self.variables = variables
        self.return_target = return_target

    def __copy__(self):
        return Frame(self.function, self.pc, deepcopy(self.variables), self.return_target)

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
        fake = bddvar('fake')
        self.value_summaries = {'_pc': [[fake.restrict({fake: 1}), 0]]}
        self.value_summaries.update({k: [[fake.restrict({fake: 1}), None]] for k in self.head_frame().variables})
        print(self.value_summaries)
        self.bdd_vars[fake] = TRUE()

    def __copy__(self):
        return State(self.path_cond, [copy(f) for f in self.frame_stack], self.base_addr, deepcopy(self.addr_map), deepcopy(self.concrete_symbolic_pointers))

    def assign_variable(self, var, val):
        old_vs = [[~self.current_guard[0] & g, v] for g, v in self.value_summaries[var]]
        print(old_vs)
        new_vs = [[self.current_guard[0] & g, v] for g, v in val]
        self.value_summaries[var] = [vs for vs in old_vs + new_vs if not vs[0].is_zero()]

    def get_variable(self, var):
        return self.value_summaries[var]

    def get_variable_type(self, var):
        if var in self.head_frame().variables:
            return self.head_frame().variables[var][0]
        else:
            return self.frame_stack[0].variables[var][0]
    def split(self, cond, pc):
        new_var = bddvar('g', self.num_vars)
        self.num_vars += 1
        new_g = bddones(1)[0]
        for v in cond:
            new_c_var = bddvar('c', self.num_vars)
            self.num_vars += 1
            self.bdd_vars[new_c_var] = v[1]
            new_g = new_g | (v[0] & new_c_var)
        self.bdd_vars[new_var] = self.current_guard[0] & new_g
        self.value_summaries['_pc'].append([new_var, pc])
        self.value_summaries['_pc'].append([~new_var, self.current_guard[1] + 1])
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