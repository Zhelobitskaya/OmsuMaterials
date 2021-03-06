/*
    Краткая теория для начала работы с массивами в С++.
    Большинство написанного аналогично языку C (static_arrays.cpp). Но имеются исключения:
      - присвоение массиву начальных значений
      - ввод/вывод в примерах
      - использование <random> из C++11

    Массив - структура данных, содержащая набор проиндексированных элементов. В языке C++
    массивы являются типизированными, то есть могут содержать значения только одного типа.
    Общий вид объявления переменной массива следующий:
        <тип> имя_переменной[<количество_элементов>];
    Примеры:
        int vec[10]; // массив из 10 элементов, имя переменной - vec
        double nums[4];
    Важно знать, что в C++ все элементы одного массива располагаются в памяти последовательно.
    <количество_элементов> (или размер массива) - должно быть положительным числом.

    Любой элемент массива может быть получен указанием переменной, за которой следует индекс элемента в
    квадратных скобках:
        std::cout << "Second element is " << vec[1] << endl;
        vec[5] = 10;
    Индексация элементов массива начинается с нуля. Последний индекс вычисляется как ( <количество_элементов> - 1 ).
    Очевидно, что индекс должен быть положительным. Таким образом, для массива vec допустимыми являются индекс
    с 0 по 9. В тоже время, компилятор не делает проверок на соотвестствие указанного индекса количеству элементов
    в массиве. То есть, для vec[10] компилятор пропустит и такое обращение:
        vec[20];
        vec[19] = 34; // или даже такое
    но успех выполнения указанных инструкций полностью зависит от среды выполнения.

    В момент объявления может быть произведена инициализация массива начальными значениями.
    На примерах (!!!отличия от C: нальзя значения для конкретных индексов массива!!!):
        float values[10]; // каждый элемент массива будет инициализирован нулём

        int array1[4] = { 3, 5, 1, -23 }; // задание начальных значений для всех 4-х элементов
        int array2[] = { 3, 5, 1, -23 };  // количество элементов можно пропустить
        int array3[4] = { 8, 9 };         // задание значений для первых двух элементов. Остальные получат значение нуль


    Кроме того, возможно задание многомерных массивов.
    Например,
        int matrix[4][4];
    Фактически, matrix[0] - это элемент массива, содержащий ещё один массив из четырёх элементов.
    Получить доступ к конкретному элементу можно с помощью двойной индексации:
        matrix[1][3] = 5;
        matrix[0][2];

    Теоретически, многомерность ничем не ограничена. Стандартом С++ гарантируется работоспособность до 31 уровня вложенности.
        float complex_matrix[5][3][6][7][10][10]; // и такое возможно.

*/

#include <iostream>
#include <clocale>     // Установка локали для Windows-консоли
#include <chrono>      // работа со временем
#include <random>      // генератор случайных чисел


// Пример заполнения массива из 20 элементов случайными числами от 0 до 1.
// В функцию передаётся объект генератора случайных чисел
void print_random_array(std::mt19937_64& gener)
{
    double real_array[20], sum{0.0};

    for (int index = 0; index < 20; index++) {
        real_array[index] = double( gener() ) / gener.max();
        std::cout << "The element " << index + 1 << " is equal to " << real_array[index] << std::endl;
        sum += real_array[index];
    }

    std::cout << "Сумма 20 элемнтов массива равна " << sum << std::endl << std::endl;
}

// Массив также можно передавать как параметр функции
// Но в этом случае обязательно должна быть передана информация о его размере
void print_int_array(int size, int int_array[])
{
    std::cout << "Печать массива..." << std::endl;
    for (int i = 0; i < size; i++)
        std::cout << int_array[i] << " ";
    std::cout << std::endl << "... окончена." << std::endl << std::endl;
}

int main()
{
    std::setlocale(LC_ALL, "RUS");

    unsigned long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 gener1( seed );

    int negative_count = 0;
    int array3D[10][10][10];
    double average = 0;

    print_random_array(gener1);

    // заполним трёхмерный массив array3D случайными числами от -5 до 5 и вычислим среденее среди всех отрицательных.
    // size_t - встроенный тип данных, предназначенный для неотрицательных целых значений
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            for (size_t k = 0; k < 10; k++) {
                array3D[i][j][k] = -5 + (gener1() % 11);
                if (array3D[i][j][k] < 0) {
                    negative_count++;
                    average += array3D[i][j][k];
                }

                std::cout << array3D[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << "----------------" << std::endl;
    }

    if (negative_count > 0) {
        std::cout << "Среденее значение отрицательных элементов " << average / negative_count << std::endl;
    } else {
        std::cout << "Не найдено отрицательных элементов в массиве" << std::endl;
    }

    int array2[] = { 3, 5, 1, -23 }, array4[8] = { 1, -7 };
    print_int_array(4, array2);
    print_int_array(8, array4);

    return 0;
}
