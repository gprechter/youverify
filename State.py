from copy import copy, deepcopy
from abc import abstractmethod, abstractproperty, ABC
from pysmt.shortcuts import TRUE, And, Not, Store, simplify, is_sat

class Frame:
    def __init__(self, function, pc, variables, return_target):
        self.function = function
        self.pc = pc
        self.variables = variables
        self.return_target = return_target

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
        self.reports = []

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


class SubState:
    records = {}
    controller = None
    def __init__(self, path_cond, frame_stack, base_addr = 1, addr_map = {0: None}, conc_sym_pointers = {}):
        self.path_cond = path_cond
        self.frame_stack = frame_stack
        self.base_addr = base_addr
        self.addr_map = addr_map
        self.concrete_symbolic_pointers = conc_sym_pointers

    def __copy__(self):
        return SubState(self.path_cond, deepcopy(self.frame_stack), self.base_addr, {k: copy(v) for k, v in self.addr_map.items()}, copy(self.concrete_symbolic_pointers))

    def assign_variable(self, var, val):
        if var in self.head_frame().variables:
            self.head_frame().variables[var] = [self.head_frame().variables[var][0], val]
        else:
            self.frame_stack[0].variables[var] = [self.frame_stack[0].variables[var][0], val]

    def get_variable(self, var):
        if var in self.head_frame().variables:
            return self.head_frame().variables[var][1]
        else:
            return self.frame_stack[0].variables[var][1]

    def get_variable_type(self, var):
        if var in self.head_frame().variables:
            return self.head_frame().variables[var][0]
        else:
            return self.frame_stack[0].variables[var][0]
    def split(self, cond, pc):
        taken_state = copy(self)
        not_taken_state = copy(self)
        taken_state.path_cond = And(cond, self.path_cond)
        not_taken_state.path_cond = And(Not(cond), self.path_cond)
        return taken_state.update_pc(pc) + not_taken_state.advance_pc(1)

    def advance_pc(self, i):
        self.head_frame().pc += i
        return [self]

    def update_pc(self, pc):
        self.head_frame().pc = pc
        return [self]

    @property
    def pc(self):
        return self.head_frame().pc

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
            target(self.controller, return_value)

    @property
    def is_finished(self):
        return (len(self.frame_stack) == 1) and self.pc >= len(self.head_frame().function.statements)