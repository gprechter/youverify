import types


def unary_operator_wrapper(f: types.FunctionType):
    """
        The wrapper takes in the original unary operator as its parameter and
        optionally returns a new function with the new behavior.

    :param f: The unary function to be wrapped.
    :return: A new unary function.
    """
    def unary_wrapped_function(operand):
        pass
    return f

def binary_operator_wrapper(f: types.FunctionType):
    """
        The wrapper takes in the original binary operator as its parameter and
        optionally returns a new function with the new behavior.

    :param f: The binary function to be wrapped.
    :return: A new binary function.
    """
    def binary_wrapped_function(a, b):
        pass
    return f