#pragma once
#include "Lib.h"

// Заменяем __interface на class с чисто виртуальными функциями
class IDistribution {
public:
    virtual double f(const double x) const = 0;
    virtual double expected_value() const = 0;
    virtual double variance() const = 0;
    virtual double asymmetry() const = 0;
    virtual double kurtosis() const = 0;
    virtual double random_var() const = 0;
    virtual std::vector<double> generate_sequence(const int n) const = 0;
    virtual std::vector<std::pair<double, double>> generate_table_of_values(const int n, const std::vector<double>& x_s = {}) const = 0;
    virtual ~IDistribution() = default; // Виртуальный деструктор для корректного удаления объектов
};

// Заменяем __interface на class с чисто виртуальными функциями
class IPersistent {
public:
    virtual void load_from_file(std::ifstream& file) = 0;
    virtual void save_to_file(std::ofstream& file) = 0;
    virtual ~IPersistent() = default; // Виртуальный деструктор для корректного удаления объектов
};