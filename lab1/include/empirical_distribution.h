#define EMPIRICAL_DISTRIBUTION_H

#include <vector>
#include <iostream>

using namespace std;

double empirical_expected_value(int n, const vector<double>& x_s);
double empirical_variance(int n, const vector<double>& x_s);
double empirical_asymmetry(int n, const vector<double>& x_s);
double empirical_kurtosis(int n, const vector<double>& x_s);
double empirical_huber(int n, double x, const vector<double>& x_s);
