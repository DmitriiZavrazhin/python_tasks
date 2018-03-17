# python_tasks
## Документация к тестовому заданию
### Вычисление требуемого значения
Исходный код функции *calculate_testing_range*, выполняющей обход древа каталогов и вычисляющий требуемое целочисленное значение путём применения арифметических операций, определяемых именем папки, к содержимему всех файлов с расширением ".txt" в папке вкупе с результатами аналогичных вычислений, применённых к вложенным папкам, представлен в файле *calculate_testing_range.py*.

* В случае отсутствия требуемой иерархической структуры программы выведет строку "Nothing to compute";
* В случае неупрощаемой структуры древа каталогов(т.е. когда в директории запуска программы одновременно присутствуют папки "add" и "mul") программа завершится с ошибкой ("Irreducible branching");
* В случае чтения "txt"-файла, содержимое которого не может быть интерпретировано как набор разделённых пробелом целых чисел, программа завершится с ошибкой IOError("Non-integral file content");
* Папки в составе древа каталогов, не содержащие в себе файлов с расширением ".txt", не влияют на вычисляемое значение.

### Примеры запуска программы вычисления требуемого значения
Для запуска программы требуется скопировать файлы с исходным кодом в требуемую директорию (например, в корневую директорию любого "тестового полигона", то есть непосредственно в `Testing_range_N`).
Ниже приведены примеры запуска программы на примере представленных "тестовых поигонов":
* Полигон #0 (данный в условии задачи):
```
user@User:~/path_to_testing_range/Testing_range_0$ python3 calculate_testing_range.py 
226
```
* Полигон #1: (проверяет поведение программы при неупрощаемой структуре древа каталогов):
```
user@User:~/path_to_testing_range/Testing_range_1$ python3 calculate_testing_range.py 
Traceback (most recent call last):
  File "calculate_testing_range.py", line 36, in <module>
    print(calculate_testing_range())
  File "calculate_testing_range.py", line 30, in calculate_testing_range
    raise OSError('Irreducible branching')
OSError: Irreducible branching

```
* Полигон #2 (проверяет поведение программы при неинтерпретируемом содержимом текстового файла):
```
user@User:~/path_to_testing_range/Testing_range_2$ python3 calculate_testing_range.py 
Traceback (most recent call last):
  File "calculate_testing_range.py", line 21, in calculate_testing_range
    numbers.extend(map(int, file.read().split()))
ValueError: invalid literal for int() with base 10: 'abcd'

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "calculate_testing_range.py", line 36, in <module>
    print(calculate_testing_range())
  File "calculate_testing_range.py", line 17, in calculate_testing_range
    numbers.append(calculate_testing_range(value))
  File "calculate_testing_range.py", line 23, in calculate_testing_range
    raise IOError('Non-integral file content')
OSError: Non-integral file content
```
* Полигон #3 проверяет поведение программы в общем случае):
```
user@User:~/path_to_testing_range/Testing_range_3$ python3 calculate_testing_range.py 
3628822
```
* Полигон #4 (проверяет поведение программы при обработке папок, не содержащих ни одного "txt"-файла):
```
user@User:~/path_to_testing_range/Testing_range_4$ python3 calculate_testing_range.py 
307
```

### Генерация "тестового полигона"
Исходный код функции *generate_testing_range*, выполняющей генерацию "тестового полигона" на основе вводимой пользователем строки, представлен в файле *generate_testing_range.py*.

Строка, описывающая создаваемую иерархию папок, обрабатывается следующим образом:
* Символ "!" в начале строки приводит к удалению уже существующего "тестового полигона";
* Символы "+" и "*" приводят к созданию папки с соответствующим именем ("add" или "mul") и последующим переходом в неё;
* В случае присутствия папки в файловой системе в неё осуществляется переход без попытки её создания.
* Символ "|" приводит к переходу в директорию на один уровень выше.
* Знаки, принадлежащие к множеству символов {023456789- }, интерпретируются как содержимое создаваемого файла.
* Файл создаётся в рабочей директории по достижении любого символа, не принадлежащего к вышеприведённому множеству, а также по завершении строки; 
* Файлы с пустым содержанием не могут быть созданы;
* Отсутствие прав доступа, необходимых для требуемой работоспособности программы, приводит к завершению работы программы с ошибкой PermissionError и соответствующим сообщением.
* Выход за пределы директории, в которой был запущен файл, не дозволен и приводит к завершению работы программы с ошибкой LevelException("Invalid current directory level").

Пример: иерархию папок, данную в условии задачи, можно создать с помощью строки
```
++1,1|*2 2,7+1 2 3,3 -1
```

### Примеры запуска программы генерации тестового полигона
* Пример успешной генерации:
```
user@User:~/some_path/some_folder$ python3 generate_testing_range.py 
++1,1|*2 2,7+1 2 3,3 -1
Success
```
* Пример некоррекной генерации:
```
user@User:~/some_path/some_folder$ python3 generate_testing_range.py 
++1,1|*2 2,7+1 2 3,3 -1||||1
Traceback (most recent call last):
  File "generate_testing_range.py", line 65, in <module>
    generate_testing_range()
  File "generate_testing_range.py", line 58, in generate_testing_range
    raise LevelException
__main__.LevelException: Invalid current directory level

```
