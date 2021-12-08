

class Statement:
    def exec(self, state):
        state.advance_pc()

class BeginMergeStatement(Statement):
    def exec(self, state):
        state.advance_pc()

class EndMergeStatement(Statement):
    def exec(self, state):
        state.advance_pc()

class VerifyStatement(Statement):
    def __init__(self, expr):
        self.expr = expr

    def exec(self, state):
        state.advance_pc()