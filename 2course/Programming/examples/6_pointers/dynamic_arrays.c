/*
    Основной материал по основам указателей в C расположен по адресу: https://github.com/posgen/OmsuMaterials/wiki/Variables-and-ponters:-basic

    Желательно ознакомиться с файлом pointers.c в той же директории, что и данный файл.

    Для повторения: массив - это набор элементов, к каждому их которых имеется доступ по индексу.
    В языке C массиивы являются:
        1) типизированными, то есть могут содержать в себе только элементы одного конкретного типа (int, float, double, char);
        2) непрерывно расположенными в памяти. Гарантируется, что все элементы массива идут друг за другом в некотором блоке оперативной памяти.

    Пункт 2) позволяет использовать указатели для работы с масивами.
    Рассмотрим статический массив целых чисел из 5 элементов:
        int arr[] = {1, 3, 5, 7, 9};

    Графически расположение этого массива в памяти можно представить вот так (для тех, кому лень было статью выше открывать):
        < 1 >< 3 >< 5 >< 7 >< 9 >
    Здесь треугольные скобки означают блок памяти, необходимый для хранения переменной определённого типа. В примере - тип int.
    То есть - это не синтаксис языка, это просто ассоциативная картинка. И она как раз показывает тот факт, что все
    элементы расположены в памяти последовательно. Размер конкретного блока равен размеру переменной конкретного типа.

    Каждый отдельный элемент массива - arr[0], arr[1], arr[2] - по сути является отдельной переменной, поэтому
    у него можно получить адрес. А раз можно получить адрес, значит можно сохранить его в указатель
        int *p_arr;
        p_arr = &arr[1];

    Здесь мы записываем адрес второго (arr[1]) элемента массива в указатель p_arr. Теперь всё выглядит примерно так:
        < 1 >< 3 >< 5 >< 7 >< 9 >
             ^
             |
           p_arr

    Через указатель p_arr и его разыменование можно изменить значение конкретного элемента массива, но всё это уже было (pointers.c).

    Следующая операция, применяемая к указателям - прибавление целого числа (как положительного, так и отрицательного).
    Например:
        p_arr++; // или p_arr += 1;

    В этом случае адрес указателя меняется путём прибавления к нему sizeof(int) байт. И p_arr теперь указывает на
    третий элемент массива:
        < 1 >< 3 >< 5 >< 7 >< 9 >
                  ^
                  |
                p_arr

    При прибавлении отрицательного числа (или вычитании положительного), адрес указателя уменьшается на
    соотвествующее число байт. Так
        p_arr -= 2; // отнимаем целое число 2 от значения указателя
    приводит к тому, что в p_arr хранится адрес первого элемента массива arr:
        < 1 >< 3 >< 5 >< 7 >< 9 >
        ^
        |
      p_arr

    Здесь стоит добавить, что за изменением адресов памяти должен следить только автор программы, сам язык
    не проверяет - содержит ли указатель корректный адрес или нет.

    Далее следует следующий факт: переменная статического массива (в рассматриваемом случае - arr) по сути
    является постоянным (в смысле - неизменным) указателем на первый элемент массива. То есть:
        < 1 >< 3 >< 5 >< 7 >< 9 >
        ^
        |
       arr

    Это легко подтверждается, попыткой вывести адрес:
        printf("The address of arr is %p", arr);
        printf("The address of first element is %p\n", &arr[0]);
    Обе функции printf выведут один и тот же адрес.

    Продолжение следует...

*/

#include <stdio.h>
#include <stdlib.h>
