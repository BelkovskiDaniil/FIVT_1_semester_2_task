/* Дан массив неотрицательных целых 64-битных чисел.
 * Количество чисел не больше 1000000.
 * Отсортировать массив методом поразрядной сортировки LSD по байтам.*/

//https://contest.yandex.ru/contest/41792/run-report/75544388/

#include <iostream>

// Берем n-ый байт числа
int byte(long long number, int n) {
    return number >> (8 * n) & 255;
}

// LSD-сортировка
void lsd_sort(long long *array, int size) {
    int bytes_length = sizeof(long long);

    for(int j = 0; j < bytes_length; j++) {

        // Сортировка массива подсчетом

        int counters[256];


        for(int i = 0; i < 256; i++) {
            counters[i] = 0;
        }

        // Сколько чисел имеют в байте различные значения
        for(int i = 0; i < size; i++) {
            counters[byte(array[i], j)]++;
        }

        // Находим первые индексы для вставки чисел
        for(int i = 1; i < 256; i++) {
            counters[i] += counters[i - 1];
        }

        long long *array_of_answers = new long long[size];

        int i = size - 1;

        // Заполняем массив с ответами
        while (true){
            array_of_answers[--counters[byte(array[i], j)]] = array[i];

            if(i == 0) {
                break;
            }

            --i;

        }

        for(int i = 0; i < size; i++) {
            array[i] = array_of_answers[i];
        }

        delete[] array_of_answers;
    }
}

int main() {
    int n = 0;
    std::cin >> n;

    long long *array = new long long[n];

    for(int i = 0; i < n; i++) {
        std::cin >> array[i];
    }

    lsd_sort(array, n);

    for(int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }

    delete[] array;

    return 0;
}