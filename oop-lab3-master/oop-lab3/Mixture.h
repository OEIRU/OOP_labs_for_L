#pragma once
#include "Lib.h"
#include "Primary.h"

class Mixture
{
private:

	double p;

	Primary* HB1;

	Primary* HB2;

public:

	Mixture();

	Mixture(Primary* HB1, Primary* HB2, double p);

	Mixture(ifstream& file);

	Primary* get_component1();

	Primary* get_component2();

	double get_p() const;

	void set_p(const double p);

	void save_to_file(ofstream& file);

	double f(const double x) const;

	double expected_value() const;

	double variance() const;

	double asymmetry() const;

	double kurtosis() const;

	double random_var() const;

	vector<double> generate_sequence(const int n) const;

	vector<pair<double, double>> generate_table_of_values(const int n, const vector<double>& x_s = {}) const;
};