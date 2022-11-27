/*Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
 * Требуется найти k-ю порядковую статистику.
 * Т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
 * Напишите нерекурсивный алгоритм.
 * Требования к дополнительной памяти: O(n).
 * Требуемое среднее время работы: O(n).
 * Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 * Описание для случая прохода от начала массива к концу:
 * Выбирается опорный элемент.
 * Опорный элемент меняется с последним элементом массива.
 * Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
 * Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы.
 * Последним элементом лежит опорный.
 * Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
 * Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
 * Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
 * Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
 * В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.*/

//https://contest.yandex.ru/contest/41792/run-report/75540404/

#include <iostream>
#include <algorithm>

//Ищем опорный элемент
int median(int* arr, int left, int mid, int right) {

    if (arr[left] > arr[mid]) {
        if (arr[right] > arr[left])
            return left;
        return (arr[mid] > arr[right]) ? mid : right;
    }

    if (arr[right] > arr[mid]) {
        return mid;
    }

    return (arr[left] > arr[right]) ? left : right;
}

// Рассечение массива и сортировка относительно опорного без рекурсии
int partition(int *arr, int left, int right) {
    int pivot = median(arr, left, (left + right) / 2, right);
    std::swap(arr[pivot], arr[right]);
    int x = arr[right];
    int i = left;

    for (int j = left; j <= right - 1; j++) {
        if (arr[j] <= x) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }

    std::swap(arr[i], arr[right]);
    return i;
}

// Поиск k - ую статистику
int k_statistic(int* arr, int k, int size) {
    int left = 0, right = size;
    while (1) {

        if (left == right) {
            return arr[left];
        }

        int mid = partition(arr, left, right);

        if (mid == k) {
            return arr[mid];
        }

        else if (k < mid) {
            right = mid - 1;
        }

        else {
            left = mid + 1;
        }

    }
}


int main() {
    int n = 0;
    int k = 0;

    std::cin >> n >> k;

    int *arr = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout << k_statistic(arr, k, n - 1) << std::endl;

    delete[] arr;

    return 0;
}