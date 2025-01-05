#include <cassert>
#include <iostream>
#include "Primary.h"
#include "Mixture.h"
#include "Empirical.h"

void test_basic_methods() {
    Primary* HB = new Primary();
    assert(std::abs(HB->get_v() - 1.) < 0.01);
    assert(std::abs(HB->get_shift() - 0.) < 0.01);
    assert(std::abs(HB->get_scale() - 1.) < 0.01);
    delete HB;
    std::cout << "test_basic_methods passed." << std::endl;
}

void test_standard_distribution() {
    Primary* HB = new Primary();
    assert(std::abs(HB->f(0) - 0.341) < 0.01);
    assert(std::abs(HB->expected_value() - 0) < 0.01);
    assert(std::abs(HB->variance() - 2.24) < 0.01);
    assert(std::abs(HB->asymmetry() - 0) < 0.01);
    assert(std::abs(HB->kurtosis() - 2.37) < 0.01);
    delete HB;
    std::cout << "test_standard_distribution passed." << std::endl;
}

void test_primary_shift_and_scaled() {
    Primary* HB = new Primary();
    HB->set_scale(2);
    HB->set_shift(2);
    assert(std::abs(HB->f(0) - 0.103) < 0.01);
    assert(std::abs(HB->expected_value() - 2) < 0.01);
    assert(std::abs(HB->variance() - 2.24) < 0.01);
    assert(std::abs(HB->asymmetry() - 0) < 0.01);
    assert(std::abs(HB->kurtosis() - 2.37) < 0.01);
    delete HB;
    std::cout << "test_primary_shift_and_scaled passed." << std::endl;
}

void test_mixture_of_distributions() {
    Mixture* MX = new Mixture();
    MX->get_component1()->set_scale(2);
    MX->get_component2()->set_scale(2);
    MX->get_component1()->set_shift(2);
    MX->get_component2()->set_shift(2);
    assert(std::abs(MX->f(0) - 0.103) < 0.01);
    assert(std::abs(MX->expected_value() - 2) < 0.01);
    assert(std::abs(MX->variance() - 2.24) < 0.01);
    assert(std::abs(MX->asymmetry() - 0) < 0.01);
    assert(std::abs(MX->kurtosis() - 1.77) < 0.01);
    delete MX;
    std::cout << "test_mixture_of_distributions passed." << std::endl;
}

void test_mixture_distribution_expected_value() {
    Mixture* MX = new Mixture();
    MX->get_component1()->set_scale(2);
    MX->get_component2()->set_scale(2);
    MX->get_component1()->set_shift(1);
    MX->get_component2()->set_shift(2);
    assert(std::abs(MX->expected_value() - 1.5) < 0.01);
    delete MX;
    std::cout << "test_mixture_distribution_expected_value passed." << std::endl;
}

void test_mixture_distribution_variance() {
    Mixture* MX = new Mixture();
    MX->get_component1()->set_scale(1);
    MX->get_component2()->set_scale(3);
    assert(std::abs(MX->variance() - 2.24) < 0.01);
    delete MX;
    std::cout << "test_mixture_distribution_variance passed." << std::endl;
}

int main() {
    test_basic_methods();
    test_standard_distribution();
    test_primary_shift_and_scaled();
    test_mixture_of_distributions();
    test_mixture_distribution_expected_value();
    test_mixture_distribution_variance();

    std::cout << "All tests passed." << std::endl;
    return 0;
}