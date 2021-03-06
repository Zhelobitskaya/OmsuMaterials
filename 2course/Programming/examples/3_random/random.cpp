/*
    Пример использования генератора (псевдо)случайных чисел.

    В стандартной библиотеке С++ используются функции из языка С.
    Отличия от random.c только в заголовочных файлах и функцях ввода/вывода

    Для получения случайных числе используется функция:
        int rand();
    из <cstdlib>. Она возращает значение от 0 до RAND_MAX.
    RAND_MAX может зависеть от стандартной C-ной библиотеки, однако гарантируется,
    что это число не будет меньше 32767. Значения, возращаемые функцией rand, - равновероятны.

    Для получения различной последовательности случайных чисел при последовательных
    запусках программы, используется функция инициализации генератора:
        void srand (unsigned int seed);
    Она принимает один аргумент - целое число - от которого зависит, какая последовательность будет выдаваться
    функцией rand(), и не возращает никакого значения.
*/

#include <iostream>
#include <cstdlib>  // srand, rand ( библиотека С для функций создания псевдослучайных чисел )
#include <ctime>    // библиотека для получения и преобразования значений времени в языке C.

using namespace std;

int main()
{
    int rnd1, rnd2;
    double rnd3;

    // Пример инициализации генератора случайных чисел постоянными значениями.
    // Два следующих вывода на экран будут показывать одни и теже числа при каждом последовательном запуске программы
    srand(123);
    cout << "First 3 numbers for seed 123 are: " << rand() << ", " << rand() << ", " << rand() << endl;

    srand(8872);
    cout << "First 3 numbers for seed 8872 are: " << rand() << ", " << rand() << ", " << rand() << endl;

    /*
        Ниже используется функция
            time(...)
        из библиотеки ctime. В данном случае - time(NULL) -, она возращает количество секунд, прошедших
        с 00:00 часов 1 января 1970 года.
        Обычно в таком виде используется инициализация генератора случайных чисел для получения различных последовательностей
        чисел при повторных запусках программы.

        Начиная со стандарта C++11 использование NULL (а это на самом деле некоторый макрос, объявленный в стандартной
        библиотеке языка C) считается нежелательным. Вместо него следует использовать ключевое слово языка C++ - nullptr
    */
    srand( time(nullptr) );

    // несколько примеров
    rnd1 = rand() % 21;      // получить случайное число от 0 до 20
    rnd2 = rand() % 10 - 5;  // получить случайное число от -5 до 4.
    /*
        В двух примерах выше используется оператор взятия остатка от целочисленного деления. Он выполняет
        поставленную задачу, то есть - позволяет получить числа в некотором диапазоне, но есть один нюанс
        с качеством получаемых значений.

        Из математики известно, что если проводить взятие остатка от деления положительного числа m на
        другое положительное n, то в качестве значений мы можем получить одно из:
            0, 1, 2, 3, ... , n-1
        В самом деле, если вспомнить операции с простыми дробыми, какое бы число не делили на 2, то остаток может быть
        только 0 или 1 (т.е. 3/2 = 1 (1/2), 6/2 = 3 (0/2)).

        Предположим, что функция rand() возращает следующий ряд из 11 чисел подряд:
            0  1  2  3  4  5  6  7  8  9  10
        А мы хотим получить "псевдослучайные" от нуля до четырёх. Для этого по выше приведённым примерам
        нужно взять остаток от целоичленного деления на 5. Тогда из ряда будут получены результаты:
           (0  1  2  3  4  5  6  7  8  9  10)
            |  |  |  |  |  |  |  |  |  |  |    %5
            v  v  v  v  v  v  v  v  v  v  v
            0  1  2  3  4  0  1  2  3  4  0
        
        Рассматривая последний ряд видно, что вероятность выпадения нуля выше, чем у всех остальных чисел.
        Это означает, что  при использовании оператора % для создания диапазона случайных чисел, нельзя полагать,
        что получаемые в итоге числа в некотором диапазоне равновероятны.

        Отсюда вывод - для учебных и тестовых программ использование оператора взятия остатка от деления особого
        вреда не принесёт, но в реальных задачах (особенно - в численных задачах науки) лучше не использовать его.
    */
    

    /*
        Получить случайное действительное число от 0 до 1.
        Здесь используется явное приведение типа int к типу double для того, чтобы операция деления была выполнена
        над действительными числами, иначе деление было целочисленными и невозможно было бы получить числа отличные
        от нуля и единицы.

        В С++ можно использовать как явное приведение типа в стиле C:
            (type) value
        , где type - тип, значение которого нужно получить; value - значение, которое нужно привести к требуемому типу.

        Так и приведение типа в функциональном стиле:
            type(value)
        Ниже используется второй вариант
    */
    rnd3 = ( double( rand() ) ) / RAND_MAX;
    /*
        Создание действительного числа в диапазоне [0; 1] позволяет преодолеть недостаток создания значений в
        некотором диапазоне с помощью оператора %. Допустим, есть функция drand_0_1 - которая даёт случайное 
        действительное число в указанном диапазоне. Тогда получить случайные числа на заданном отрезке [a; b]
        можно по формуле:
            a + (b - a) * drand_0_1()
        Из-за особенностей приведения действительных чисел к целым, данная формула верна как для типа int, так и 
        для double.  
    */

    cout << "random number1: " << rnd1 << endl << "random number2: " << rnd2 << endl << "random number3: " << rnd3 << endl;
    return 0;
}
