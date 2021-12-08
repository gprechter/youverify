from copy import copy, deepcopy
from abc import abstractmethod, abstractproperty, ABC
from pyeda.inter import *
from pysmt.shortcuts import TRUE, FALSE, And, Not, Or, simplify, is_sat, Int, FreshSymbol, INT, Symbol, ArrayType, get_model, get_free_variables
from YouVerifyArray import YouVerifyArray
from Statement import BeginMergeStatement, EndMergeStatement

class Frame:
    def __init__(self, function, pc, variables, return_target):
        self.function = function
        self.pc = pc
        self.variables = variables
        self.return_target = return_target

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

class State(ABC):

    @abstractmethod
    def next_state(self):
        pass

    @abstractproperty
    def current_statement(self):
        pass

    @abstractmethod
    def assign_variable(self, var, val):
        pass

    @abstractmethod
    def get_variable(self, var):
        pass

    @abstractmethod
    def advance_pc(self, i):
        pass

    @abstractmethod
    def unconditional_branch(self, pc):
        pass

    @abstractmethod
    def conditional_branch(self, cond, pc):
        pass

    @abstractmethod
    def add_path_constraint(self, cond):
        pass

class DefaultState(State):
    def __init__(self, sub_states):
        self.current_state = None
        self.sub_states = sub_states

    @property
    def current_statement(self):
        return self.current_state.current_statement

    def assign_variable(self, var, val):
        self.current_state.assign_variable(var, val)

    def get_variable(self, var):
        return self.current_state.get_variable(var)

    def advance_pc(self, i=1):
        self.current_state = self.current_state.advance_pc(i)

    def unconditional_branch(self, pc):
        self.current_state = self.current_state.update_pc(pc)

    def conditional_branch(self, cond, pc):
        self.current_state = self.current_state.split(cond, pc)

    def next_state(self):
        if self.current_state:
            for s in [s for s in self.current_state if is_sat(s.path_cond)]:
                self.sub_states.append(s)

        if self.sub_states and any([not s.is_finished for s in self.sub_states]):
            for i, s in enumerate(self.sub_states):
                if not s.is_finished:
                    self.current_state = self.sub_states.pop(i)
                    return True
        return False

    def add_path_constraint(self, cond):
        self.current_state.path_cond = And(self.current_state.path_cond, cond)

class ObliCheckState(State):
    bdd_vars = {}
    num_vars = 0
    merge_statements = []
    verification_condition = None
    added_symbols = {}
    unmerged = []
    def __init__(self, head_frame):
        self.head_frame = head_frame
        self.value_summaries = {'_pc': [[PathConstraint(), 0]]}
        self.value_summaries.update({k: [[PathConstraint(), Int(0)]] for k in self.head_frame.variables})
        is_merging = False
        for i, stmt in enumerate(self.head_frame.function.statements):
            if isinstance(stmt, BeginMergeStatement):
                is_merging = True
            elif isinstance(stmt, EndMergeStatement):
                is_merging = False
            else:
                if is_merging:
                    ObliCheckState.merge_statements.append(i)
        ObliCheckState.verification_condition = self.head_frame.function.statements.pop()




    @property
    def current_statement(self):
        return self.head_frame.function.statements[self.current_guard[1]]

    def assign_variable(self, var, val):
        merge = {}
        old_vs = [[self.current_guard[0].apply_NOT().apply_AND(g), v] for g, v in self.value_summaries[var]]
        new_vs = [[self.current_guard[0].apply_AND(g), copy(v) if isinstance(v, YouVerifyArray) else v] for g, v in val]

        if self.current_guard[1] in self.merge_statements and 'length' not in var and var not in self.unmerged:
            new_guard = PathConstraint()
            new_value = None
            for g, v in old_vs + new_vs:
                new_guard = new_guard.apply_OR(g)
            new_value = YouVerifyArray(0, length=v.length, array=[FreshSymbol(ArrayType(INT, INT))]) if isinstance(v, YouVerifyArray) else FreshSymbol(INT)
            if isinstance(new_value, YouVerifyArray):
                if new_value.get_array().symbol_name() in self.added_symbols:
                    self.added_symbols[new_value.get_array().symbol_name()].append(var)
                else:
                    self.added_symbols[new_value.get_array().symbol_name()] = [var]
            else:
                if new_value.symbol_name() in self.added_symbols:
                    self.added_symbols[new_value.symbol_name()].append(var)
                else:
                    self.added_symbols[new_value.symbol_name()] = [var]
            vs = [[new_guard, new_value]]
        else:
            vs = old_vs + new_vs

        for g, v in vs:
            if not g.is_zero() and not g.is_unsat():
                if v not in merge:
                    merge[v] = g
                else:
                    merge[v] = merge[v].apply_OR(g)
        self.value_summaries[var] = [[v, k] for k, v in merge.items()]

    def get_variable(self, var):
        return self.value_summaries[var]

    def advance_pc(self, i=1):
        self.current_guard = [self.current_guard[0], self.current_guard[1] + 1]
        self.value_summaries['_pc'].append(self.current_guard)

    def unconditional_branch(self, pc):
        self.current_guard = [self.current_guard[0], pc]
        self.value_summaries['_pc'].append(self.current_guard)

    def conditional_branch(self, cond, pc, guard = None):
        new_g = PathConstraint().apply_NOT()
        for g, v in cond:
            new_g = new_g.apply_OR(g.apply_AND(PathConstraint().from_condition(v)))
        if not (self.current_guard[0].apply_AND(new_g).is_zero() or self.current_guard[0].apply_AND(new_g).is_unsat()):
            self.value_summaries['_pc'].append([self.current_guard[0].apply_AND(new_g), pc])
        if not (self.current_guard[0].apply_AND(new_g.apply_NOT()).is_zero() or self.current_guard[0].apply_AND(
                new_g.apply_NOT()).is_unsat()):
            self.value_summaries['_pc'].append(
                [self.current_guard[0].apply_AND(new_g.apply_NOT()), self.current_guard[1] + 1])

    def next_state(self):
        merge = {}
        for g, v in self.value_summaries['_pc']:
            if not g.is_zero() and not g.is_unsat():
                if v not in merge:
                    merge[v] = g
                else:
                    merge[v] = merge[v].apply_OR(g)
        self.value_summaries['_pc'] = [[v, k] for k, v in merge.items()]
        if any([not (v >= len(self.head_frame.function.statements)) for c, v in self.value_summaries['_pc']]):

            i = min(range(len(self.value_summaries['_pc'])), key = lambda i: self.value_summaries['_pc'][i][1])
            self.current_guard = self.value_summaries['_pc'].pop(i)
            return True
        if False and self.verification_condition:
            for g,v in self.verification_condition.expr.eval(self):
                if not get_model(g.pc).get_value(v).constant_value():

                    for v in get_free_variables(g.pc):
                        if v.symbol_name() in self.added_symbols:
                            self.unmerged.extend(self.added_symbols[v.symbol_name()])
                            self.value_summaries = {'_pc': [[PathConstraint(), 0]]}
                            self.value_summaries.update({k: [[PathConstraint(), Int(0)]] for k in self.head_frame.variables})
                            PathConstraint.bdd_vars = {}
                            PathConstraint.num_vars = 0
                            self.current_guard = self.value_summaries['_pc'].pop()
                            return True
        return False

    def add_path_constraint(self, cond):
        self.current_state.path_cond = And(self.current_state.path_cond, cond)