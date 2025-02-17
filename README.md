# Test_task
A test assignment for an intern for the position of "C++ Programmer" at Infotecs

Задание состоит из двух программ и библиотеки, которые необходимо реализовать.

Взаимодействие программ должно быть реализовано через использование сокетов.

Библиотека

Должна быть динамической и состоять из трёх функций.

Функция 1. Сортирует элементы входной строки по убыванию и все четные элементы заменяет на
латинские буквы «КВ». Функция не возвращает никакого значения.

Функция 2. Рассчитывает и возвращает общую сумму всех элементов входной строки, которые
являются численными значениями.

Функция 3. Анализирует, из скольки символов состоит входная строка. Если оно больше 2-ух
символов и, если оно кратно 32, то функция возвращает «истина». В противном случае функция
возвращает «ложь».

Программа №1.

Должна состоять из двух потоков и одного общего буфера.

Поток 1. Принимает строку, которую введет пользователь. Должна быть проверка, что строка
состоит только из цифр и не превышает 64 символа. После проверки строка передается на
обработку функции 1. Затем обработанная строка помещается в общий буфер и поток должен
ожидать дальнейшего ввода пользователя.

Поток 2. Должен обрабатывать данные которые помещаются в общий буфер. После получения
данных общий буфер затирается. Поток должен вывести полученные данные на экран, а также
передать эти данные функции 2. Значение, возвращенное функцией, передать в Программу №2.
После этого поток ожидает следующие данные.

Примечание №1 по Программе №1: Взаимодействие потоков должно быть синхронизировано,
поток №2 не должен постоянно опрашивать общий буфер.

Примечание №2 по Программе №1: Работа программы должна быть максимально независима
от статуса запуска программы №2. Это значит, что внезапный останов программы №2 не
должен приводить к немедленным проблемам ввода у пользователя.
При перезапуске программы №2 необходимо произвести передподключение.

Программа №2.

Ожидает данные от Программы №1. При получении данных передаёт их функции 3. Если функция
вернула значение «истина», то программа выводит сообщение о полученных данных, иначе
выводится сообщение об ошибке. Далее программа продолжает ожидать данные.

Примечание №1 по Программе №2: Работа программы должна быть максимально независима
от статуса запуска программы №1. Внезапный останов программы №1 не должен приводить
к немедленным проблемам отображения. Необходимо ожидать подключение программы №1
при потере связи между программами.

Примечание по заданию: Не обязательно все размещать в одном классе. Может быть разработана
иерархия классов. Чем более функционален интерфейс класса, тем лучше.

Сборка и запуск:
в папке Test_task 
mkdir build
cd build
cmake ..
make
make install

в папке build
cd Program_2
./Program_2

Открыть новый терминал, перейти в папку build
cd Program_1
./Program_1

В терминале, где запущена программа 1 вводить строки без пробела
