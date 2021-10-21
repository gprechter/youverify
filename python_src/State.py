from copy import copy

from pysmt.shortcuts import TRUE, And, Not, Store

class Frame:
    def __init__(self, function, pc, variables, return_target):
        self.function = function
        self.pc = pc
        self.variables = variables
        self.return_target = return_target

    def __copy__(self):
        return Frame(self.function, self.pc, self.variables.copy(), self.return_target)

class State:

    def __init__(self, path_cond, frame_stack):
        self.path_cond = path_cond
        self.frame_stack = frame_stack

    def __copy__(self):
        return State(self.path_cond, [copy(f) for f in self.frame_stack])

    def assign_variable(self, var, val):
        if var in self.head_frame().variables:
            self.head_frame().variables[var] = val
        else:
            self.frame_stack[0].variables[var] = val

    def get_variable(self, var):
        if var in self.head_frame().variables:
            return self.head_frame().variables[var]
        else:
            return self.frame_stack[0].variables[var]
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
            self.assign_variable(target.name, return_value)

    @property
    def is_finished(self):
        return (len(self.frame_stack) == 1) and self.pc >= len(self.head_frame().function.statements)