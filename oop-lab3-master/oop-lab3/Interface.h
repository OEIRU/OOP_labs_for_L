#pragma once
#include "Primary.h"
#include "Mixture.h"
#include "Empirical.h"

void step3_primary(Primary* HB);

void step3_mixture(Mixture* MX);

void step3_empirical(Empirical* EM);

void step2_primary();

void step2_mixture();

void step2_empirical_from_primary();

void step2_empirical_from_mixture();

void step2_empirical_from_empirical();

void step2_empirical_from_sequence();

void step2_empirical();

void step1();

void start();