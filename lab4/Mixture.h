#ifndef MIXTURE_H
#define MIXTURE_H

#include <iostream>
#include <cmath>
#include <stdexcept>

template <typename T1, typename T2>
class Mixture {
private:
    T1* component1; // Первый компонент смеси
    T2* component2; // Второй компонент смеси
    double p;       // Вероятность выбора первого компонента

public:
    // Конструктор
    Mixture(T1* comp1, T2* comp2, double probability)
        : component1(comp1), component2(comp2), p(probability) {
        if (p < 0 || p > 1) {
            throw std::invalid_argument("Вероятность должна быть в диапазоне [0, 1]");
        }
    }

    // Деструктор
    ~Mixture() {
        delete component1;
        delete component2;
    }

    // Получить первый компонент
    T1* get_component1() const {
        return component1;
    }

    // Получить второй компонент
    T2* get_component2() const {
        return component2;
    }

    // Плотность распределения в точке x
    double f(double x) const {
        return p * component1->f(x) + (1 - p) * component2->f(x);
    }

    // Математическое ожидание
    double expected_value() const {
        return p * component1->expected_value() + (1 - p) * component2->expected_value();
    }

    // Дисперсия
    double variance() const {
        double mean1 = component1->expected_value();
        double mean2 = component2->expected_value();
        double var1 = component1->variance();
        double var2 = component2->variance();
        return p * (var1 + mean1 * mean1) + (1 - p) * (var2 + mean2 * mean2) - std::pow(expected_value(), 2);
    }

    // Асимметрия
    double asymmetry() const {
        double mean = expected_value();
        double std_dev = std::sqrt(variance());
        double skew1 = component1->asymmetry();
        double skew2 = component2->asymmetry();
        return p * skew1 + (1 - p) * skew2; // Упрощенная формула для асимметрии смеси
    }

    // Эксцесс
    double kurtosis() const {
        double kurt1 = component1->kurtosis();
        double kurt2 = component2->kurtosis();
        return p * kurt1 + (1 - p) * kurt2; // Упрощенная формула для эксцесса смеси
    }
};

#endif // MIXTURE_H