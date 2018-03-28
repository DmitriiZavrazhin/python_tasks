#!/usr/bin/python3
import os
import argparse

SYMBOLS = '0123456789- '
OPERATORS = {'+': 'add', '*': 'mul'}


def write_to_file(new_file_index, new_file_content):
    try:
        with open('file' + (str(new_file_index) if new_file_index > 0 else '') + '.txt', 'w') as file:
            file.write(new_file_content)
    except PermissionError:
        print('Insufficient writing permissions')


def clean_testing_range():
    for value in OPERATORS.values():
        if os.path.isdir(value):
            for root, directories, files in os.walk(value, topdown=False):
                for name in files:
                    os.remove(os.path.join(root, name))
                for name in directories:
                    os.rmdir(os.path.join(root, name))
            os.rmdir(value)


def generate_testing_range(descriptor):
    new_file_content = ''
    new_file_index = 0
    level = 0
    if descriptor[0] == '!':
        clean_testing_range()
    for char in descriptor:
        if char not in SYMBOLS and new_file_content != '':
            write_to_file(new_file_index, new_file_content)
            new_file_content = ''
            new_file_index += 1
        if char in OPERATORS.keys():
            try:
                if not os.path.isdir(OPERATORS[char]):
                    os.mkdir(OPERATORS[char])
                os.chdir(OPERATORS[char])
                level += 1
            except PermissionError:
                print('Insufficient permissions to operate with a folder')
                return
        elif char == '|':
            os.chdir('../')
            level -= 1
        elif char in SYMBOLS:
            new_file_content += char
        if level < 0:
            print('Invalid current directory level')
            return
    if new_file_content != '':
        write_to_file(new_file_index, new_file_content)
    print('Success')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='This program generates a testing range by given descriptor.')
    parser.add_argument('-p', '--path', type=str, default='./', help='the path to the working directory')
    parser.add_argument('-d', '--descr', type=str, default='', help='the descriptor cn be also specified as a command line argument')
    args = parser.parse_args()
    os.chdir(args.path)
    generate_testing_range(args.descr if args.descr != '' else input())
