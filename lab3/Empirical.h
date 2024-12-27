#pragma once
#include "Lib.h"
#include "Primary.h"
#include "Mixture.h"

class Empirical
{
private:

	vector<double> x_s;

	vector<double> f_s;

	int n = 0;

	int k = 0;

public:

	Empirical(const Primary* HB, int _n, int _k);

	Empirical(const Mixture* MX, int _n, int _k);

	Empirical(const Empirical* EM);

	Empirical(const int _n, const int _k);

	Empirical(const vector<double>& x_s);

	Empirical(ifstream& file);

	~Empirical();

	Empirical& operator=(const Empirical& EM);

	double random_var() const;

	vector<double> generate_x_s() const;

	vector<double> generate_f_s() const;

	vector<pair<double, double>> generate_table_of_values() const;

	vector<double> get_x_s() const;

	vector<double> get_f_s() const;

	int get_n() const;

	int get_k() const;

	void save_to_file(ofstream& file);

	double f(const double x) const;

	double expected_value() const;

	double variance() const;

	double asymmetry() const;

	double kurtosis() const;
};
