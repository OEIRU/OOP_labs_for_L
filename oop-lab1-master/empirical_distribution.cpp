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
double empirical_huber(int n, double x, vector<double> x_s)
{

    vector<double> f_s;
    int k = (int)trunc(log2((double)n)) + 1;     // Определяем количество интервалов k
    double min_x = *min_element(begin(x_s), end(x_s));
    double max_x = *max_element(begin(x_s), end(x_s));
    // Вычисляем ширину интервала
    double delta = (max_x - min_x) / (double)k;

    // Проходим по всем интервалам
    for (int i = 0; i < k; i++)
    {

        // Проверяем, попадает ли x в текущий интервал
        if (min_x + delta * i <= x && x < min_x + delta * (i + 1))
        {
            // Считаем количество элементов в текущем интервале
            int n_i = count_if(x_s.begin(), x_s.end(), [i, k, min_x, max_x, delta](double x) { return i == k - 1 ? min_x + delta * (double)i <= x && x <= min_x + delta * (double)(i + 1) : min_x + delta * (double)i <= x && x < min_x + delta * (double)(i + 1); });
            return n_i / (n * delta);
        }
    }
}

// Функция для генерации последовательности значений на основе распределения Хубера
vector<double> generate_sequence(int n, HuberDistribution* HB)
{
    vector<double> x_s;

    for (int i = 0; i < n; i++)
    {
        double x = calculate_x(HB);
        x_s.push_back(x);
    }

    return x_s;
}