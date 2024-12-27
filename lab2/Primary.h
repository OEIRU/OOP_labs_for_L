#pragma once
#include "lib.h"

class Primary
{
private:

	double v;

	double k;

	double scale;

	double shift;

public:

	Primary(double v = 1, double scale = 1, double shift = 0);

	Primary(ifstream& file);

	void save_to_file(ofstream& file) const;

	void load_from_file(ifstream& file);

	double get_v() const;

	void set_v(const double v);

	double get_k() const;

	double get_scale() const;

	void set_scale(const double scale);

	double get_shift() const;

	void set_shift(const double shift);

	double f(const double x) const;

	double phi(const double x) const;

	double phi_lower(const double x) const;

	double expected_value() const;

	double variance() const;

	double asymmetry() const;

	double kurtosis() const;

	double P() const;

	double K(const double v) const;

	double random_var() const;

	vector<double> generate_sequence(const int n) const;

	vector<pair<double, double>> generate_table_of_values(const int n, const vector<double>& x_s = {}) const;
};