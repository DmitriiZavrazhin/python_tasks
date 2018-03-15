import os
import glob
from functools import reduce
from operator import mul

folder_names = {'+': 'add', '*': 'mul'}

folds = {'add': sum,
         'mul': lambda x: reduce(mul, x)}


def calculate_testing_range_(a='./'):
    os.chdir(a)
    numbers = []
    contents = os.listdir("./")
    for value in folder_names.values():
        if value in contents:
            numbers.append(calculate_testing_range_('./' + value))
    for file_ in glob.glob('*.txt'):
        with open(file_, 'r') as file:
            numbers.extend(map(int, file.read().split()))
    folder = os.getcwd().rpartition('/')[2]
    os.chdir("../")
    if folder in folds.keys():
        return folds[folder](numbers)
    elif len(numbers) > 0:
        return numbers[-1]
    else:
        return "Nothing to compute"


print(calculate_testing_range_())
