/* Группа людей называется современниками если был такой момент, когда они могли собраться вместе.
 * Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не исполниться 80 лет.
 * Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников.
 * В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
 * Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия.
 * В этих случаях принимать участие в собраниях он не мог.*/

//https://contest.yandex.ru/contest/41792/run-report/75537422/

#include <iostream>
#include <vector>

// Структура, хранящая данные о возрасте личности (дата с которой он мог встречать людей, и после которой не мог)
struct age {
    int day;
    int month;
    int year;
    bool dead;
    age() : day(0), month(0), year(0), dead(false) {}
    age(int day, int month, int year, bool dead);
    bool operator>(const age &other) const;
    bool operator<(const age &other) const;
};

age::age(int day, int month, int year, bool dead) {
    this->day = day;
    this->month = month;
    this->year = year;
    this->dead = dead;
}

// Переопределяем оператор для сравнения данных этого типа (оператор помогает вычислить кто родился раньше или позже)
bool age::operator>(const age &other)const  {
    return (year > other.year) || (year == other.year && month > other.month) ||
           (month == other.month && year == other.year && day > other.day) ||
           (month == other.month && year == other.year && day == other.day && dead < other.dead);
}

// Переопределяем оператор для сравнения данных этого типа (оператор помогает вычислить кто родился раньше или позже)
bool age::operator<(const age &other) const {
    return (year < other.year) ||
           (year == other.year && month < other.month) ||
           (month == other.month && year == other.year && day < other.day) ||
           (month == other.month && year == other.year && day == other.day && dead > other.dead);
}

// Функция пирамидальной сортировки, сдвигающая элемент от корня в в ветвь
void sift_down(std::vector<age> &a, int size, int i) {
    int biggest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && a[left] > a[biggest]) {
        biggest = left;
    }
    if (right < size && a[right] > a[biggest]) {
        biggest = right;
    }

    if (biggest != i) {
        std::swap(a[i], a[biggest]);
        sift_down(a, size, biggest);
    }
}

// Создание пирамиды (кучи)
void build_heap(std::vector<age> &a) {
    for (int i = a.size() / 2 - 1; i >= 0; --i) {
        sift_down(a, a.size(), i);
    }
}

// Пирамидальная сортировка
void heap_sort(std::vector<age> &a) {
    int heap_size = a.size();
    build_heap(a);
    while (heap_size > 1) {
        std::swap(a[0], a[heap_size - 1]);
        --heap_size;
        sift_down(a, heap_size, 0);
    }
}

// Ищем максимальное количество пересечений
int maximal_age(std::vector<age> &a) {
    int max = 0, local_max = 0;

    for (int i = 0; i < a.size();++i) {

        if (!a[i].dead) {
            ++local_max;
        }

        else {
            --local_max;
        }

        local_max > max ? max = local_max : local_max = local_max;
    }

    return max;
}

int main() {
    int n = 0, start_day = 0, start_month = 0, start_year = 0, end_day = 0, end_month = 0, end_year = 0;
    std::cin >> n;
    std::vector<age> array(n * 2);

    for (int i = 0; i <  array.size();) {

        std::cin >> start_day >> start_month >> start_year >> end_day >> end_month >> end_year;

        // Заменяем дату смерти на дату окончания возможности встреч
        if (end_year - start_year > 80 || (end_year - start_year == 80 && end_month - start_month >= 0 && end_day - start_day >= 0)) {
            end_year = start_year + 80;
            end_month = start_month;
            end_day = start_day;
        }

        // Заменяем дату рождения на дату начала возможности встреч
        if (end_year - start_year >= 18) {
            start_year += 18;
        }

        // Если личность умерла до 18 лет
        else {
            start_day = end_day = start_month = end_month = start_year = end_year = -1;
        }

        age data_1(start_day, start_month, start_year, 0);
        age data_2(end_day, end_month, end_year, 1);

        array[i++] = data_1;
        array[i++] = data_2;
    }

    heap_sort(array);

    std::cout << maximal_age(array) << std::endl;

    return 0;
}