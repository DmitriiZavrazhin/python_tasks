#!/usr/bin/python3
import os
from glob import glob
import argparse


def product(obj):
    result = 1
    for x in obj:
        result *= x
    return result


OPERATORS = {'+': 'add', '*': 'mul'}
FOLDS = {'add': sum, 'mul': product}


def calculate_testing_range(node='./'):
    os.chdir(node)
    numbers = []
    for value in OPERATORS.values():
        if value in os.listdir('./'):
            numbers.append(calculate_testing_range(value))
    for file_ in glob('*.txt'):
        with open(file_, 'r') as file:
            try:
                numbers.extend(map(int, file.read().split()))
            except ValueError:
                return 'Non-integral file content'
    os.chdir("../")
    if node in FOLDS.keys():
        return FOLDS[node](numbers)
    elif len(numbers) == 1:
        return numbers[0]
    elif len(numbers) > 1: 
        return 'Irreducible branching'
    else:
        return 'Nothing to compute'


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='This program calculates an integer value of given testing range.')
    parser.add_argument('-p', '--path', type=str, default='./', help='the path to the working directory')
    args = parser.parse_args()
    os.chdir(args.path)
    print(calculate_testing_range())
