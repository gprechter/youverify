import sys
import json
import glob
import os.path
from YouVerify import main, concrete_evaluation

def compare_json(a, b):
    print("EXPECTED:", json.dumps(b, sort_keys=True))
    print("GOT:\t ", json.dumps(a, sort_keys=True))

    return json.dumps(a, sort_keys=True) == json.dumps(b, sort_keys=True)

def check(state, file):
    return compare_json(json.loads(state), json.load(open(file, 'r')))

def check_all(dir):
    for file in glob.glob(dir + "/**/*.yvr", recursive=True):
        print(file)
        expected = glob.glob(dir + f"/**/{os.path.basename(file).split('.')[0]}.expected", recursive=True)
        if expected:
            print("PASS" if check(concrete_evaluation(main(["testing", file])), expected[0]) else "FAILED")

check_all(sys.argv[1])