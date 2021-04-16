import json
import sys

with open("./expected/%s.json" % sys.argv[1], 'r') as expected:
    expected_variables = json.loads(expected.read())
    for name, val in json.loads(sys.stdin.read()).items():
        assert name in expected_variables, "FAIL: Variable does not exist."
        assert val == expected_variables[name], "FAIL: Expected %s, got %s." % (expected_variables[name], val)
    print("PASS")
