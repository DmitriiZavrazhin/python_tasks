#!/usr/bin/python3
import os
from glob import glob
from functools import reduce
from operator import mul


operators = {'+': 'add', '*': 'mul'}
folds = {'add': sum,
         'mul': lambda x: reduce(mul, x) if x != [] else 1}


def calculate_testing_range(node='./'):
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
    if node in folds.keys():
        return folds[node](numbers)
    elif len(numbers) == 1:
        return numbers[-1]
    elif len(numbers) > 1:
        return 'Irreducible branching'
    else:
        return 'Nothing to compute'


if __name__ == '__main__':
    print(calculate_testing_range())
