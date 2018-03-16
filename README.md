# python_tasks
## Документация к тестовому заданию
### Вычисление требуемого значения
Исходный код функции *calculate_testing_range*, выполняющей обход древа каталогов и вычисляющий требуемое целочисленное значение путём применения арифметических операций, определяемых именем папки, к содержимему всех файлов с расширением ".txt" в папке вкупе с результатами аналогичных вычислений, применённых к вложенным папкам, представлен в файле *calculate_testing_range.py*.

* В случае отсутствия требуемой иерархической структуры программы выведет строку "Nothing to compute";
* В случае неупрощаемой структуры древа каталогов(т.е. когда в директории запуска программы одновременно присутствуют папки "add" и "mul") программа завершится с ошибкой ("Irreducible branching");
* В случае чтения "txt"-файла, содержимое которого не может быть интерпретировано как набор разделённых пробелом целых чисел, программа завершится с ошибкой IOError("Non-integral file content");
* Папки в составе древа каталогов, не содержащие в себе файлов с расширением ".txt", не влияют на вычисляемое значение.

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
