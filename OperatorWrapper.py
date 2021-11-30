def unary_operator_wrapper(f):
    def unary_wrapped_function(operand):
        pass
    return f

def binary_operator_wrapper(f):
    def binary_wrapped_function(a, b):
        new_vs = []
        for lvs in a:
            for rvs in b:
                new_vs.append([lvs[0].apply_AND(rvs[0]), f(lvs[1], rvs[1])])
        return new_vs
    return binary_wrapped_function