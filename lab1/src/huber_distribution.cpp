#include "huber_distribution.h"

// Функция для инициализации распределения Хьюбера
// v - параметр, определяющий границу перехода между квадратичной и линейной частями
// K - параметр, связанный с масштабом распределения
// scale - параметр, влияющий на ширину распределения
// shift - смещение, сдвигающее распределение по оси x
HuberDistribution* init_huber_distribution(double v, double K, double scale, double shift)
{
    HuberDistribution* HB = new HuberDistribution();
    HB->v = v;
    HB->K = K;
    HB->scale = scale;
    HB->shift = shift;
    return HB;
}

// Функция для вычисления значения функции плотности вероятности распределения
// x - значение, для которого вычисляется плотность вероятности
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

// Функция для отладки, записывающая информацию в файл
void log_huber_debug(const string& message) {
    ofstream log_file("huber_debug.log", ios_base::app);  // Открытие файла для добавления в конец
    if (log_file.is_open()) {
        log_file << message << endl;  // Запись в файл
        log_file.close();
    }
}

// Функция Хубера с отладочной информацией
double Huber(double x, HuberDistribution* HB)
{
    // Отладка: вывод значения x и параметров распределения
    stringstream debug_message;
    debug_message << "распределенное x = " << x << endl;
    debug_message << "HB->shift = " << HB->shift << ", HB->scale = " << HB->scale << ", HB->K = " << HB->K << ", HB->v = " << HB->v;
    log_huber_debug(debug_message.str());

    double abs_diff = abs((x - HB->shift) / HB->scale);  // Разность с учетом масштаба
    stringstream debug_msg_interval;
    
    if (abs_diff <= HB->v) {
        // Отладка: вывод значений внутри условия
        debug_msg_interval << "x в пределах в = " << HB->v << ", abs_diff = " << abs_diff;
        log_huber_debug(debug_msg_interval.str());
        double result = exp(-pow(abs_diff, 2.) / 2.);
        log_huber_debug("Используется нормальное распределение с результатом: " + to_string(result));
        return result / (sqrt(2. * M_PI) * HB->K * HB->scale);  // Нормальная часть
    } else {
        // Отладка: вывод значений в случае, если abs_diff > v
        debug_msg_interval.str("");  // Очищаем строковый поток
        debug_msg_interval << "x вне предела в = " << HB->v << ", abs_diff = " << abs_diff;
        log_huber_debug(debug_msg_interval.str());
        double result = exp(pow(HB->v, 2.) / 2. - HB->v * abs_diff);
        log_huber_debug("Используется экспоненциальное распределение с результатом: " + to_string(result));
        return result / (sqrt(2. * M_PI) * HB->K * HB->scale);  // Экспоненциальная часть
    }
}

// Функция для вычисления значения распределения стандартного нормального распределения
// x - значение, для которого вычисляется вероятность
double phi(double x)
{
    return 0.5 * (1. + erf(x / sqrt(2.)));
}

// Функция для вычисления значения плотности вероятности стандартного нормального распределения
// x - значение, для которого вычисляется плотность вероятности
double phi_lower(double x)
{
    // Использование формулы для вычисления плотности вероятности
    // стандартного нормального распределения
    return 1. / sqrt(2. * M_PI) * exp(-1. / 2. * pow(x, 2.));
}

// Функция для вычисления математического ожидания распределения
double huber_expected_value(HuberDistribution* HB)
{
    // Математическое ожидание распределения Хубера равно смещению
    return HB->shift;
}

// Функция для вычисления дисперсии распределения 
double huber_variance(HuberDistribution* HB)
{

    return 1. + 2. * phi_lower(HB->v) * (pow(HB->v, 2.) + 2.) / (pow(HB->v, 3.) * HB->K);
}

// Функция для вычисления асимметрии распределения 
double huber_asymmetry(HuberDistribution* HB)
{
    // В данном случае асимметрия распределения равна 0
    return 0.;
}

// Функция для вычисления эксцесса распределения Хубера
double huber_kurtosis(HuberDistribution* HB)
{
    return (3. * (2. * phi(HB->v) - 1.) +
        2. * phi_lower(HB->v) *
        (24. / pow(HB->v, 5.) +
            24. / pow(HB->v, 3.) +
            12. / HB->v + HB->v)) /
        (pow(huber_variance(HB), 2.) * HB->K) - 3.;
}

// Функция для вычисления вероятности (P) для распределения 
double P(HuberDistribution* HB)
{
    // Вычисление вероятности на основе функции phi и параметра K
    return (2. * phi(HB->v) - 1.) / HB->K;
}

// Функция для вычисления некоторой функции K на основе параметра v
double K(double v)
{
    return 2. / v * phi_lower(v) + 2. * phi(v) - 1.;
}

// Функция для генерации случайного значения на основе распределения
double calculate_x(HuberDistribution* HB)
{
    // Инициализация генератора случайных чисел
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<> dist(0, 1);

    // Генерация случайного числа для проверки вероятности
    double r1 = dist(gen);

    if (r1 <= P(HB))
    {
        // Генерация равномерного случайного числа в диапазоне [-v, v]
        double x1;
        do {
            x1 = (dist(gen) * 2 - 1) * HB->v; // Преобразование к диапазону [-v, v]
        } while (!(x1 >= -HB->v && x1 <= HB->v)); // Проверка, что x1 находится в пределах [-v, v]

        // Масштабирование и сдвиг результата
        return x1 * HB->scale + HB->shift;
    }
    else
    {
        // Генерация случайного числа для вычисления x2
        double r4 = dist(gen);

        // Вычисление x2 для другой части распределения
        double x2 = HB->v - log(r4) / HB->v;

        // Возврат значения с учётом симметрии распределения
        return (r1 < (1 + P(HB)) / 2)
            ? x2 * HB->scale + HB->shift
            : -x2 * HB->scale + HB->shift;
    }
}