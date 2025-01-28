#include "empirical_distribution.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

// Функция для вычисления эмпирического математического ожидания
double empirical_expected_value(int n, const vector<double>& x_s) {
    if (n <= 0 || x_s.empty()) {
        cout << "Некорректный ввод: n <= 0 или выборка пуста" << endl;
        return 0.0;
    }

    double sum = 0;
    for (double x : x_s) {  // Суммируем все значения в векторе
        sum += x;
    }
    return sum / n;  // Возвращаем среднее значение
}

// Функция для вычисления эмпирической дисперсии
double empirical_variance(int n, const vector<double>& x_s) {
    if (n <= 0 || x_s.empty()) {
        cout << "Некорректный ввод: n <= 0 или выборка пуста" << endl;
        return 0.0;
    }

    double expected_value = empirical_expected_value(n, x_s);  // Математическое ожидание
    double sum = 0;

    // Суммируем квадраты отклонений от математического ожидания
    for (double x : x_s) {
        sum += pow(x - expected_value, 2);
    }

    return sum / n;  // Возвращаем дисперсию
}

// Функция для вычисления эмпирической асимметрии
double empirical_asymmetry(int n, const vector<double>& x_s) {
    if (n <= 0 || x_s.empty()) {
        cout << "Некорректный ввод: n <= 0 или выборка пуста" << endl;
        return 0.0;
    }

    double expected_value = empirical_expected_value(n, x_s);  // Математическое ожидание
    double variance = empirical_variance(n, x_s);              // Дисперсия

    if (variance == 0) {
        cout << "Дисперсия равна нулю, асимметрия не определена" << endl;
        return 0.0;
    }

    double sum = 0;
    // Суммируем кубы отклонений от математического ожидания
    for (double x : x_s) {
        sum += pow(x - expected_value, 3);
    }

    return sum / (n * pow(variance, 1.5));  // Возвращаем асимметрию
}

// Функция для вычисления эксцесса
double empirical_kurtosis(int n, const vector<double>& x_s) {
    if (n <= 0 || x_s.empty()) {
        cout << "Некорректный ввод: n <= 0 или выборка пуста" << endl;
        return 0.0;
    }

    double expected_value = empirical_expected_value(n, x_s);  // Математическое ожидание
    double variance = empirical_variance(n, x_s);              // Дисперсия

    if (variance == 0) {
        cout << "Дисперсия равна нулю, эксцесс не определен" << endl;
        return 0.0;
    }

    double sum = 0;
    // Суммируем четвертые степени отклонений от математического ожидания
    for (double x : x_s) {
        sum += pow(x - expected_value, 4);
    }

    return (sum / (n * pow(variance, 2))) - 3;  // Возвращаем эксцесс
}

// Функция для вычисления значения функции Хубера (эмпирическая плотность)
double empirical_huber(int n, double x, const vector<double>& x_s) {
    if (n <= 0 || x_s.empty()) {
        cout << "Некорректный ввод: n <= 0 или выборка пуста" << endl;
        return 0.0;
    }

    // Определяем количество интервалов
    int k = max(5, static_cast<int>(trunc(log2(static_cast<double>(n))) + 1));

    // Находим минимальное и максимальное значение в выборке
    double min_x = *min_element(x_s.begin(), x_s.end());
    double max_x = *max_element(x_s.begin(), x_s.end());

    // Ширина интервала
    double delta = (max_x - min_x) / static_cast<double>(k);

    // Проверка, что x находится в пределах выборки
    if (x < min_x || x > max_x) {
        cout << "x вне диапазона выборки" << endl;
        return 0.0;
    }

    // Поиск интервала, в который попадает x
    for (int i = 0; i < k; ++i) {
        double lower_bound = min_x + delta * i;
        double upper_bound = min_x + delta * (i + 1);

        // Для последнего интервала учитываем правую границу
        if (i == k - 1) {
            upper_bound = max_x;
        }

        if (x >= lower_bound && x <= upper_bound) {
            // Подсчет количества элементов в интервале
            int n_i = count_if(x_s.begin(), x_s.end(),
                               [lower_bound, upper_bound](double val) {
                                   return (val >= lower_bound) && (val <= upper_bound);
                               });

            // Вычисление плотности
            double density = static_cast<double>(n_i) / (n * delta);
            return density;
        }
    }

    return 0.0;  // Если x не попал ни в один интервал (не должно происходить)
}