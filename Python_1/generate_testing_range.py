import os

operators = {'+': 'add', '*': 'mul'}


def write_to_file(new_file_index, new_file_content):
    try:
        with open('file' + (str(new_file_index) if new_file_index > 0 else '') + '.txt', 'w') as file:
            file.write(new_file_content)
    except PermissionError:
        raise PermissionError('Insufficient writing permissions')


def generate_testing_range(descriptor=input()):
    new_file_content = ''
    new_file_index = 0
    for char in descriptor:
        if char not in '0123456789- ' and new_file_content != '':
            write_to_file(new_file_index, new_file_content)
            new_file_content = ''
            new_file_index += 1
        if char in operators.keys():
            try:
                if not os.path.isdir(operators[char]):
                    os.mkdir(operators[char])
                os.chdir(operators[char])
            except PermissionError:
                raise PermissionError('Insufficient permissions'
                                      ' to operate with a folder')
        elif char == '|':
            os.chdir('../')
        elif char in '0123456789- ':
            new_file_content += char
    if new_file_content != '':
        write_to_file(new_file_index, new_file_content)


if __name__ == '__main__':
    generate_testing_range()
