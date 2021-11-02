import sys
import json
import glob
import os.path
from YouVerify import main, concrete_evaluation, display_states_smt2

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

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
            print((bcolors.BOLD + bcolors.OKGREEN + "PASS" + bcolors.ENDC)
                  if check(concrete_evaluation(main(["testing", file])), expected[0]) else
                  (bcolors.BOLD + bcolors.FAIL + "FAILED" + bcolors.ENDC))
        else:
            display_states_smt2(main(['eval', file]))

check_all(sys.argv[1])