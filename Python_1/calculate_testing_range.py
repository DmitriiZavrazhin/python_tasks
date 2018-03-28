#!/usr/bin/python3
import os, sys
from glob import glob
from functools import reduce
from operator import mul


def calculate_testing_range(node='./'):
    operators = {'+': 'add', '*': 'mul'}
    folds = {'add': sum,
             'mul': lambda x: reduce(mul, x) if x != [] else 1}
    os.chdir(node)
    numbers = []
    for value in operators.values():
        if value in os.listdir('./'):
            numbers.append(calculate_testing_range(value))
    for file_ in glob('*.txt'):
        with open(file_, 'r') as file:
            try:
                numbers.extend(map(int, file.read().split()))
            except ValueError:
                return 'Non-integral file content'
    os.chdir("../")
    if node in folds.keys(): # if it is to be reduced, do reduce
        return folds[node](numbers)
    elif len(numbers) == 1: # but if it is target directory and everything is reduced to only one number, 
                            # then we extract that one number; as target directory named add/mul does not intrudes 
                            # into the calculation result, we can have a guarantee that in every case it is valid to do so, 
                            # and this step will result in a correct return value for every valid case.
        return numbers[-1] # it's identical to "return numbers[0]", but the current realisation seems more logical to me.
    elif len(numbers) > 1: 
        return 'Irreducible branching'
    else:
        return 'Nothing to compute'


if __name__ == '__main__':
    if len(sys.argv) > 2:
        if sys.argv[1] in ['-p', '--path']:
            os.chdir(sys.argv[2])
    print(calculate_testing_range())
