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
double Huber(double x, HuberDistribution* HB)
{
    return (1. / (sqrt(2. * M_PI) * HB->K) * (abs((x - HB->shift) / HB->scale) <= HB->v ? exp(-pow((x - HB->shift) / HB->scale, 2.) / 2.) : exp(pow(HB->v, 2.) / 2. - HB->v * abs((x - HB->shift) / HB->scale)))) / HB->scale;
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
    cout << HB->v <<endl;
    cout << HB->K << endl;

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
    std::uniform_real_distribution<> d(0, 1);

    // Шаг 1: Генерация равномерного случайного числа r1
    double r1 = d(gen);
    // Проверка, попадает ли r1 в область вероятности распределения Хубера
    if (r1 <= P(HB))
    {
        // Шаг 2: Генерация двух случайных чисел для метода Бокса-Мюллера
        double r2, r3, x1;
        // Шаг 3: Генерация нормального случайного числа x1
        do {
            r2 = d(gen);
            r3 = d(gen);
            // Применение метода Бокса-Мюллера для генерации нормального распределения
            x1 = sqrt(-2 * log(r2)) * cos(2 * M_PI * r3);
            //double x1 = sqrt(-2 * log(r2)) * sin(2 * M_PI * r3)
        } while (!(-HB->v <= x1 && x1 <= HB->v)); 
        // Условие для ограничения x1 в интервале [-v, v]

        return x1 * HB->scale + HB->shift;
        // Возвращение сгенерированного значения, масштабированного и смещенного
    }
    else
    {
        // Шаг 4: Генерация случайного числа r4 для другой части распределения
        double r4 = d(gen);
        // Вычисление x2 на основе распределения
        double x2 = HB->v - log(r4) / HB->v;

        // Шаг 5: Возвращение значения с учетом симметрии распределения
        return r1 < (1 + P(HB)) / 2 ? x2 * HB->scale + HB->shift : -x2 * HB->scale + HB->shift;
    }
}

