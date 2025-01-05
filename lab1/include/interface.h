#ifndef INTERFACE_H
#define INTERFACE_H

#include "huber_distribution.h"
#include "mixture_distribution.h"
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

void file_output_distribution(int n, vector<double>& x_s, HuberDistribution* HB);
void file_output_mixture(int n, vector<double>& x_s, Mixture* M);
void general_distribution();
void mixture_distribution();
void interface();

#endif