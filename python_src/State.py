from copy import copy, deepcopy
from abc import abstractmethod, ABC
from pysmt.shortcuts import TRUE, And, Not, Store, simplify, is_sat

class Frame:
    def __init__(self, function, pc, variables, return_target):
        self.function = function
        self.pc = pc
        self.variables = variables
        self.return_target = return_target

class State(ABC):

    @abstractmethod
    def current_state(self):
        pass

    @abstractmethod
    def next_state(self):
        pass

    @abstractmethod
    @property
    def current_statement(self):
        pass

    @abstractmethod
    def assign_variable(self, var, val):
        pass

    @abstractmethod
    def get_variable(self, var, val):
        pass

    @abstractmethod
    def unconditional_branch(self, pc):
        pass

    @abstractmethod
    def conditional_branch(self, pc):
        pass

class DefaultState(State):
    def __init__(self, sub_states):
        self._current_state = None
        self.sub_states = sub_states

    def current_state(self):
        return self._current_state

    @property
    def current_statement(self):
        return self._current_state.current_statement()

    def next_state(self):
        if self.current_state() and is_sat(self.current_state):
            self.sub_states.append(self.current_state())
        if self.sub_states:
            self._current_state = self.sub_states.pop(0)
            return True
        else:
            return False



class SubState:
    records = {}
    def __init__(self, path_cond, frame_stack, base_addr = 1, addr_map = {0: None}, conc_sym_pointers = {}):
        self.path_cond = path_cond
        self.frame_stack = frame_stack
        self.base_addr = base_addr
        self.addr_map = addr_map
        self.concrete_symbolic_pointers = conc_sym_pointers

    def __copy__(self):
        return State(self.path_cond, deepcopy(self.frame_stack), self.base_addr, {k: copy(v) for k, v in self.addr_map.items()}, copy(self.concrete_symbolic_pointers))

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
        taken_state.update_pc(pc).path_cond = And(cond, self.path_cond)
        not_taken_state.advance_pc().path_cond = And(Not(cond), self.path_cond)
        return [taken_state, not_taken_state]

    def advance_pc(self):
        self.head_frame().pc += 1
        return self

    def update_pc(self, pc):
        self.head_frame().pc = pc
        return self

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
            target(self, return_value)

    @property
    def is_finished(self):
        return (len(self.frame_stack) == 1) and self.pc >= len(self.head_frame().function.statements)