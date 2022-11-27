/*Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся замкнутую ломаную, проходящую через все эти точки.
 * Предполагается, что никакие три точки не лежат на одной прямой.
 * Стройте ломаную от точки, имеющей наименьшую координату x.
 * Если таких точек несколько, то используйте точку с наименьшей координатой y.
 * Точки на ломаной расположите в порядке убывания углов лучей от начальной точки до всех остальных точек.
 * Для сортировки точек реализуйте алгоритм сортировки вставками.
 *
 * В первой строке записано единственное число — число точек N. N ≤ 10000.
 * В последующих N строках записаны координаты точек xi, yi. Все координаты целочисленные xi, yi ≤ 100000.*/

//https://contest.yandex.ru/contest/41792/run-report/75535047/


#include <iostream>
#include <cmath>

struct Point
{
    double x;
    double y;
    double angle;
};

//Сортировка вставками по углу наклона (по арктангенсу) отрезка к точке
void sorting(struct Point* array, int n) {
    int i, j;
    double buff = 0.0;
    for (i = 1; i < n; ++i){
        buff = array[i].angle;
        for (j = i; j > 1 && buff > array[j - 1].angle; --j)
            std::swap(array[j], array[j - 1]);
    }
}

//Рассчет арктангенса угла для каждой точки
void angles(struct Point* array, int n) {
    for (int i = 1; i < n; i++) {
        if (array[i].x == array[0].x) {
            array[i].angle = 6.28;
        }
        else {
            array[i].angle = atan((array[i].y - array[0].y) / (array[i].x - array[0].x));
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    Point array[n];

    for (int i = 0; i < n; i++){
        std::cin >> array[i].x >> array[i].y;
    }

    //Задаем "начальную" точку
    double buffer_first = array[0].x;
    double buffer_second = array[0].y;

    int j = 0;

    // Ищем "наименьшую" (по условию) точку с которой начнем построение линии
    for (int i = 0; i < n; ++i) {
        if (((array[i].x < buffer_first)) || (array[i].x == buffer_first && array[i].y < buffer_second)) {
            j = i;
            buffer_first = array[i].x;
            buffer_second = array[i].y;
        }
    }

    std::swap(array[0], array[j]);

    angles(array, n);

    sorting(array, n);

    for (int i = 0; i < n; ++i)
        std::cout << array[i].x << ' ' << array[i].y << std::endl;

    return 0;
}
