import os

folder_names = {'+': 'add', '*': 'mul'}


def get_index(x):
    return str(x) if x > 0 else ''


def generate_testing_range():
    new_file_content = ''
    new_file_index = 0
    descriptor = input()
    for char in descriptor:
        if char not in '0123456789- ' and new_file_content != '':
            with open('file' + get_index(new_file_index) + '.txt', 'w') as file:
                file.write(new_file_content)
            new_file_content = ''
            new_file_index += 1
        if char in folder_names.keys():
            os.mkdir(folder_names[char])
            os.chdir(folder_names[char])
        elif char == '|':
            os.chdir('../')
        elif char in '0123456789- ':
            new_file_content += char
    if new_file_content != '':
        with open('file' + get_index(new_file_index) + '.txt', 'w') as file:
            file.write(new_file_content)


generate_testing_range()
