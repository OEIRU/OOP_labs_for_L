#ifndef HUBER_DISTRIBUTION_H
#define HUBER_DISTRIBUTION_H

#include <vector>

using namespace std;

// Структура для хранения параметров распределения Хубера
struct HuberDistribution {
    double v;
    double K;
    double scale;
    double shift;
};

// Прототипы функций
HuberDistribution* init_huber_distribution(double v, double K, double scale, double shift);
double Huber(double x, HuberDistribution* HB);
double phi(double x);
double phi_lower(double x);
double huber_expected_value(HuberDistribution* HB);
double huber_variance(HuberDistribution* HB);
double huber_asymmetry(HuberDistribution* HB);
double huber_kurtosis(HuberDistribution* HB);
double P(HuberDistribution* HB);
double K(double v);
double calculate_x(HuberDistribution* HB);

// Добавь объявление generate_sequence
vector<double> generate_sequence(int n, HuberDistribution* HB);

#endif