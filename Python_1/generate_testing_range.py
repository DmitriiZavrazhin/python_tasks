import os

operators = {'+': 'add', '*': 'mul'}
symbols = '0123456789- '


def write_to_file(new_file_index, new_file_content):
    try:
        with open('file' + (str(new_file_index) if new_file_index > 0 else '') + '.txt', 'w') as file:
            file.write(new_file_content)
    except PermissionError:
        print('Insufficient writing permissions')


def clean_testing_range():
    for value in operators.values():
        if os.path.isdir(value):
            for root, directories, files in os.walk(value, topdown=False):
                for name in files:
                    os.remove(os.path.join(root, name))
                for name in directories:
                    os.rmdir(os.path.join(root, name))
            os.rmdir(value)


def generate_testing_range(descriptor=input()):
    new_file_content = ''
    new_file_index = 0
    level = 0
    if descriptor[0] == '!':
        clean_testing_range()
    for char in descriptor:
        if char not in symbols and new_file_content != '':
            write_to_file(new_file_index, new_file_content)
            new_file_content = ''
            new_file_index += 1
        if char in operators.keys():
            try:
                if not os.path.isdir(operators[char]):
                    os.mkdir(operators[char])
                os.chdir(operators[char])
                level += 1
            except PermissionError:
                print('Insufficient permissions to operate with a folder')
                return
        elif char == '|':
            os.chdir('../')
            level -= 1
        elif char in symbols:
            new_file_content += char
        if level < 0:
            print('Invalid current directory level')
            return
    if new_file_content != '':
        write_to_file(new_file_index, new_file_content)
    print('Success')


if __name__ == '__main__':
    generate_testing_range()
