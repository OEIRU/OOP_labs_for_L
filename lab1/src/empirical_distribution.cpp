#include "empirical_distribution.h"

// Функция для вычисления эмпирического математического ожидания
double empirical_expected_value(int n, vector<double> x_s)
{
    double sum = 0;
    for (double& x : x_s)     // Суммируем все значения в векторе
        sum += x;
    return sum / n;           // Возвращаем среднее значение
}

// Функция для вычисления эмпирической дисперсии
double empirical_variance(int n, vector<double> x_s)
{
    // Вычисляем эмпирическое математическое ожидание
    double expected_value = empirical_expected_value(n, x_s);
    double sum = 0;
    // Суммируем квадраты отклонений от математического ожидания
    for (double& x : x_s)
        sum += pow(x - expected_value, 2);
    // Возвращаем дисперсию
    return sum / n;
}

// Функция для вычисления эмпирической асимметрии
double empirical_asymmetry(int n, vector<double> x_s)
{
    // Вычисляем эмпирическое математическое ожидание и дисперсию
    double expected_value = empirical_expected_value(n, x_s);
    double variance = empirical_variance(n, x_s);

    // Суммируем кубы отклонений от математического ожидания
    double sum = 0;
    for (double& x : x_s)
        sum += pow(x - expected_value, 3);

    return 1 / (n * pow(variance, 3 / 2)) * sum;
}

// Функция для вычисления эксцесса 
double empirical_kurtosis(int n, vector<double> x_s)
{
    // Вычисляем эмпирическое математическое ожидание и дисперсию
    double expected_value = empirical_expected_value(n, x_s);
    double variance = empirical_variance(n, x_s);

    // Суммируем четвертые степени отклонений от математического ожидания
    double sum = 0;
    for (double& x : x_s)
        sum += pow(x - expected_value, 4);

    // Возвращаем эксцесс, вычитая 3 для приведения к стандартному определению
    return 1 / (n * pow(variance, 2)) * sum - 3;
}

// Функция для вычисления значения функции Хубера
// Функция для вычисления значения функции Хубера
double empirical_huber(int n, double x, vector<double> x_s)
{
    cout << "эмперическое x = " << x << endl;

    // Проверка на корректность входных данных
    if (n <= 0 || x_s.empty()) {
        cout << "Некорректный ввод: n <= 0 или выборка пуста" << endl;
        return 0.0; // Обработка некорректного ввода или пустой выборки
    }

    int k = std::max(5, (int)trunc(log2((double)n)) + 1); // Минимум 5 интервалов
    cout << "Количество интервалов (k): " << k << endl;

    double min_x = *min_element(x_s.begin(), x_s.end());
    double max_x = *max_element(x_s.begin(), x_s.end());

    cout << "min_x = " << min_x << ", max_x = " << max_x << endl;

    if (min_x == max_x) {
        cout << "Все значения одинаковы, плотность не определена" << endl;
        return 0.0; // Все значения одинаковы, плотность не определена
    }

    double delta = (max_x - min_x) / (double)k; // Ширина интервала
    cout << "Ширина интервала (delta): " << delta << endl;

    if (x < min_x || x > max_x) {
        cout << "x вне диапазона выборки" << endl;
        return 0.0; // x вне диапазона выборки
    }

    // Подсчет количества элементов в интервале для каждого i
    for (int i = 0; i < k; ++i)
    {
        double lower_bound = min_x + delta * i;
        double upper_bound = min_x + delta * (i + 1);
        bool in_interval = (x >= lower_bound) && (x < upper_bound);

        // Для последнего интервала проверяем правую границу
        if (i == k - 1) {
            upper_bound = max_x;
            in_interval = (x <= upper_bound);
        }

        //cout << "Интервал [" << lower_bound << ", " << upper_bound << "]: ";
        //cout << "x " << (in_interval ? "попадает" : "не попадает") << " в интервал." << endl;

        if (in_interval)
        {
            // Считаем количество элементов в текущем интервале
            int n_i = count_if(x_s.begin(), x_s.end(),
                               [lower_bound, upper_bound](double val) {
                                   return (val >= lower_bound) && (val < upper_bound);
                               });

            //cout << "Количество элементов в интервале: " << n_i << endl;

            // Для последнего интервала учтем правую границу
            if (i == k - 1)
            {
                n_i += count_if(x_s.begin(), x_s.end(),
                                [lower_bound, upper_bound](double val) {
                                    return val >= lower_bound && val <= upper_bound;
                                });
            }

            double density = (double)n_i / (n * delta); // Эмпирическая плотность
            cout << "Эмпирическая плотность в интервале: " << density << endl;
            return density;
        }
    }

    return 0.0; // Не должно быть достигнуто
}


// Функция для генерации последовательности значений на основе распределения Хубера
vector<double> generate_sequence(int n, HuberDistribution* HB)
{
    vector<double> x_s;

    for (int i = 0; i < n; ++i)
    {
        // Используем функцию calculate_x для генерации значений
        double x = calculate_x(HB);
        x_s.push_back(x);
    }

    return x_s;
}
