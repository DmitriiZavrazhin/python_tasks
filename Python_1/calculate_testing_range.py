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
    contents = os.listdir("./")
    for value in operators.values():
        if value in contents:
            numbers.append(calculate_testing_range('./' + value))
    for file_ in glob('*.txt'):
        with open(file_, 'r') as file:
            try:
                numbers.extend(map(int, file.read().split()))
            except ValueError:
                raise IOError('Non-integral file content')
    current_folder = os.getcwd().rpartition('/')[2]
    os.chdir("../")
    if current_folder in folds.keys():
        return folds[current_folder](numbers)
    elif node == './' and len(numbers) == 1:
        return numbers[-1]
    elif len(numbers) > 1:
        raise OSError('Irreducible branching')
    else:
        return "Nothing to compute"


if __name__ == '__main__':
    print(calculate_testing_range())
