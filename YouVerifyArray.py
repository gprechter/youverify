from pysmt.shortcuts import Array, Int, INT

class YouVerifyArray:
    def __init__(self, default_value=0, length=None, array=None, index=Int(0)):
        self.default_value = default_value
        self.length = length
        self.index = index
        if array:
            self._array = array
        else:
            self._array = [Array(INT, default_value)]

    def get_array(self):
        return self._array[0]

    def set_array(self, array):
        self._array[0] = array