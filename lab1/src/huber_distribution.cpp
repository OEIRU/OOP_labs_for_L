#include "huber_distribution.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <vector>

using namespace std;

// Функция для инициализации распределения Хубера
HuberDistribution* init_huber_distribution(double v, double K, double scale, double shift) {
    HuberDistribution* HB = new HuberDistribution();
    HB->v = v;
    HB->K = K;
    HB->scale = scale;
    HB->shift = shift;
    return HB;
}



// Функция Хубера с отладочной информацией
double Huber(double x, HuberDistribution* HB) {
    //stringstream debug_message;
    //debug_message << "распределенное x = " << x << endl;
    //debug_message << "HB->shift = " << HB->shift << ", HB->scale = " << HB->scale << ", HB->K = " << HB->K << ", HB->v = " << HB->v;
    //log_huber_debug(debug_message.str());

    double abs_diff = abs((x - HB->shift) / HB->scale);

    if (abs_diff <= HB->v) {
        double result = exp(-pow(abs_diff, 2.) / 2.);
        return result / (sqrt(2. * M_PI) * HB->K * HB->scale);
    } else {
        double result = exp(pow(HB->v, 2.) / 2. - HB->v * abs_diff);
        return result / (sqrt(2. * M_PI) * HB->K * HB->scale);
    }
}

// Функция для вычисления значения распределения стандартного нормального распределения
double phi(double x) {
    return 0.5 * (1. + erf(x / sqrt(2.)));
}

// Функция для вычисления значения плотности вероятности стандартного нормального распределения
double phi_lower(double x) {
    return 1. / sqrt(2. * M_PI) * exp(-1. / 2. * pow(x, 2.));
}

// Функция для вычисления математического ожидания распределения
double huber_expected_value(HuberDistribution* HB) {
    return HB->shift;
}

// Функция для вычисления дисперсии распределения
double huber_variance(HuberDistribution* HB) {
    return 1. + 2. * phi_lower(HB->v) * (pow(HB->v, 2.) + 2.) / (pow(HB->v, 3.) * HB->K);
}

// Функция для вычисления асимметрии распределения
double huber_asymmetry(HuberDistribution* HB) {
    return 0.;
}

// Функция для вычисления эксцесса распределения Хубера
double huber_kurtosis(HuberDistribution* HB) {
    return (3. * (2. * phi(HB->v) - 1.) +
        2. * phi_lower(HB->v) *
        (24. / pow(HB->v, 5.) +
            24. / pow(HB->v, 3.) +
            12. / HB->v + HB->v)) /
        (pow(huber_variance(HB), 2.) * HB->K) - 3.;
}

// Функция для вычисления вероятности (P) для распределения
double P(HuberDistribution* HB) {
    return (2. * phi(HB->v) - 1.) / HB->K;
}

// Функция для вычисления некоторой функции K на основе параметра v
double K(double v) {
    return 2. / v * phi_lower(v) + 2. * phi(v) - 1.;
}

// Функция для генерации случайного значения на основе распределения
double calculate_x(HuberDistribution* HB) {
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<> dist(0, 1);

    double r1 = dist(gen);

    if (r1 <= P(HB)) {
        double x1;
        do {
            x1 = (dist(gen) * 2 - 1) * HB->v;
        } while (!(x1 >= -HB->v && x1 <= HB->v));

        return x1 * HB->scale + HB->shift;
    } else {
        double r4 = dist(gen);
        double x2 = HB->v - log(r4) / HB->v;
        return (r1 < (1 + P(HB)) / 2)
            ? x2 * HB->scale + HB->shift
            : -x2 * HB->scale + HB->shift;
    }
}

// Функция для генерации последовательности значений на основе распределения Хубера
vector<double> generate_sequence(int n, HuberDistribution* HB) {
    vector<double> x_s;

    for (int i = 0; i < n; ++i) {
        double x = calculate_x(HB);
        x_s.push_back(x);
    }

    return x_s;
}