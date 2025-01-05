#pragma once
#include "Distributions.h"

class Empirical : public IDistribution, public IPersistent {
private:
    std::vector<double> x_s;
    std::vector<double> f_s;
    int n = 0;
    int k = 0;

public:
    Empirical(const IDistribution* D, int _n, int _k);
    Empirical(const Empirical* EM);
    Empirical(const int _n, const int _k);
    Empirical(const std::vector<double>& x_s);
    Empirical(std::ifstream& file);
    ~Empirical();

    Empirical& operator=(const Empirical& EM);

    double random_var() const override;
    std::vector<double> generate_sequence(const int n) const override;
    std::vector<double> generate_values() const;
    std::vector<std::pair<double, double>> generate_table_of_values(const int n, const std::vector<double>& x_s = {}) const override;

    std::vector<double> get_x_s() const;
    std::vector<double> get_f_s() const;
    int get_n() const;
    int get_k() const;

    void save_to_file(std::ofstream& file) override;
    void load_from_file(std::ifstream& file) override;

    double f(const double x) const override;
    double expected_value() const override;
    double variance() const override;
    double asymmetry() const override;
    double kurtosis() const override;
};