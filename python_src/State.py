from pysmt.shortcuts import TRUE, And, Not
class State:
    def __init__(self, program, pc=0, path_cond=TRUE(), variables={}):
        self.pc = pc
        self.path_cond = path_cond
        self.variables = variables.copy()
        self.program = program

    def split(self, cond, pc):
        return [State(self.program, pc, And(cond, self.path_cond), self.variables.copy()),
                State(self.program, self.pc + 1, And(Not(cond), self.path_cond), self.variables.copy())]
    def advance_pc(self):
        self.pc += 1
        return self

    def update_pc(self, pc):
        self.pc = pc
        return self