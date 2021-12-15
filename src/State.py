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
    """
    Abstract class template for a representation of State in *YouVerify*.
    """

    @abstractmethod
    def update_state(self):
        """
            This abstract method is invoked by the framework when before the next
            statement is to be executed. This gives the :code:`State` object the opportunity
            to modify the backend and setup for the next
            statement execution. A developer would modify this to change
            how the paths of a program are explored and how state is handled.

        :return: :code:`True` if there is more state to be executed, :code:`False` otherwise.
        :rtype: bool
        """
        pass

    @abstractproperty
    def current_statement(self):
        """
            This abstract property is invoked to retrieve the next statement to be executed by
            the symbolic interpreter.

        :return: The next :code:`Statement` object to be *executed*.
        :rtype: Statement
        """
        pass

    @abstractmethod
    def store_variable(self, var: str, val: object):
        """
            This abstract method is invoked when the framework wants to assign a value to a variable.

        :param var: The identifier of the variable being assigned to.
        :param val: The value to be assigned to the variable.
        :return: None
        """
        pass

    @abstractmethod
    def load_variable(self, var: str):
        """
            This abstract method is invoked when an identifier is evaluated and a variable is
            to be fetched from the state's variable store.

        :param var: The identifier of the variable that will be retrieved.
        :return: The value of the variable that was retrieved.
        """
        pass

    @abstractmethod
    def advance_pc(self, i: int):
        """
            This abstract method is invoked when the framework wants to advance the program counter.

        :param i: The number of statements to advance through.
        :return: None
        """
        pass

    @abstractmethod
    def jump(self, destination: int):
        """
            This abstract method is invoked when the framework reaches an unconditional branching statement.

        :param destination: The destination program counter for the branch.
        :return: None
        """
        pass

    @abstractmethod
    def conditional_branch(self, cond: object, destination: int):
        """
            This abstract method is invoked when the framework reaches a conditional branching statement. Here,
            a developer would likely want to implement state splitting.

        :param cond: The condition guarding the branch.
        :param destination: The destination program counter for the branch.
        :return: None
        """
        pass

    @abstractmethod
    def assume(self, cond: object):
        """
            This abstract method is invoked when the framework wants to add an assumption to the current state.

        :param cond: The condition to be affixed to the path constraint.
        :return: None
        """
        pass

class DefaultState(State):
    inputs = {}
    def __init__(self, sub_states):
        self.current_state = None
        self.sub_states = sub_states
        self.reports = []

    @property
    def current_statement(self):
        return self.current_state.current_statement

    def store_variable(self, var, val):
        self.current_state.store_variable(var, val)

    def load_variable(self, var):
        return self.current_state.load_variable(var)

    def advance_pc(self, i=1):
        self.current_state = self.current_state.advance_pc(i)

    def jump(self, destination):
        self.current_state = self.current_state.update_pc(destination)

    def conditional_branch(self, cond, destination):
        self.current_state = self.current_state.split(cond, destination)

    def update_state(self):
        if self.current_state:
            for s in [s for s in self.current_state if is_sat(s.path_cond)]:
                self.sub_states.append(s)

        if self.sub_states and any([not s.is_finished for s in self.sub_states]):
            for i, s in enumerate(self.sub_states):
                if not s.is_finished:
                    self.current_state = self.sub_states.pop(i)
                    return True
        return False

    def assume(self, cond):
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
        self.trace = ""
        self.indentation = 0

    def __copy__(self):
        new = SubState(self.path_cond, deepcopy(self.frame_stack), self.base_addr, {k: copy(v) for k, v in self.addr_map.items()}, copy(self.concrete_symbolic_pointers))
        new.trace = self.trace
        new.indentation = self.indentation
        return new

    def store_variable(self, var, val):
        if var in self.head_frame().variables:
            self.head_frame().variables[var] = [self.head_frame().variables[var][0], val]
        else:
            self.frame_stack[0].variables[var] = [self.frame_stack[0].variables[var][0], val]

    def load_variable(self, var):
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
        self.trace += "\t"*self.indentation
        self.trace += f"{self.pc}"
        inverted_labels = {v: k for k, v in self.head_frame().function.labels.items()}
        if self.pc in inverted_labels:
            self.trace += f" {inverted_labels[self.pc]}"
        self.trace += "\n"
        return self.head_frame().function.statements[self.pc]

    def head_frame(self):
        return self.frame_stack[-1]

    def push_frame(self, frame):
        self.trace += f"call {frame.function.name}\n"
        self.indentation += 1
        self.frame_stack.append(frame)

    def pop_frame(self, return_value):
        self.trace += f"return {self.head_frame().function.name}\n"
        self.indentation -= 1
        target = self.frame_stack.pop().return_target
        if target is not None and return_value is not None:
            target(self.controller, return_value)

    @property
    def is_finished(self):
        return (len(self.frame_stack) == 1) and self.pc >= len(self.head_frame().function.statements)