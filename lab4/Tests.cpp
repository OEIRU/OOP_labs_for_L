#include <cassert>
#include <iostream>
#include "Primary.h"
#include "Mixture.h"
#include "Empirical.h"

void test_basic_methods() {
    Primary* HB = new Primary();
    assert(std::abs(HB->get_v() - 1) < 0.01);
    assert(std::abs(HB->get_shift() - 0) < 0.01);
    assert(std::abs(HB->get_scale() - 1) < 0.01);
    delete HB;
    std::cout << "test_basic_methods passed." << std::endl;
}

void test_standard_distribution() {
    Primary* HB = new Primary();
    assert(std::abs(HB->f(0) - 0.34) < 0.01);
    assert(std::abs(HB->expected_value() - 0) < 0.01);
    assert(std::abs(HB->variance() - 2.24) < 0.01);
    assert(std::abs(HB->asymmetry() - 0) < 0.01);
    assert(std::abs(HB->kurtosis() - 2.37) < 0.01);
    delete HB;
    std::cout << "test_standard_distribution passed." << std::endl;
}

void test_shift_scale_transformation() {
    Primary* HB = new Primary();
    HB->set_scale(2);
    HB->set_shift(2);
    assert(std::abs(HB->f(0) - 0.103) < 0.01);
    assert(std::abs(HB->expected_value() - 2) < 0.01);
    assert(std::abs(HB->variance() - 2.24) < 0.01);
    assert(std::abs(HB->asymmetry() - 0) < 0.01);
    assert(std::abs(HB->kurtosis() - 2.37) < 0.01);
    delete HB;
    std::cout << "test_shift_scale_transformation passed." << std::endl;
}

void test_mixture_distribution() {
    Primary* HB1 = new Primary();
    Primary* HB2 = new Primary();
    HB1->set_scale(2);
    HB2->set_scale(2);
    HB1->set_shift(2);
    HB2->set_shift(2);
    Mixture<Primary, Primary>* MX = new Mixture<Primary, Primary>(HB1, HB2, 0.5);

    assert(std::abs(MX->f(0) - 0.103) < 0.01);
    assert(std::abs(MX->expected_value() - 2) < 0.01);
    assert(std::abs(MX->variance() - 2.24) < 0.01);
    assert(std::abs(MX->asymmetry() - 0) < 0.01);
    assert(std::abs(MX->kurtosis() - 1.77) < 0.01);

    delete MX;
    std::cout << "test_mixture_distribution passed." << std::endl;
}

void test_mixture_distribution_expected_value() {
    Primary* HB1 = new Primary();
    Primary* HB2 = new Primary();
    HB1->set_scale(2);
    HB2->set_scale(2);
    HB1->set_shift(1);
    HB2->set_shift(2);
    Mixture<Primary, Primary>* MX = new Mixture<Primary, Primary>(HB1, HB2, 0.5);

    assert(std::abs(MX->expected_value() - 1.5) < 0.01);

    delete MX;
    std::cout << "test_mixture_distribution_expected_value passed." << std::endl;
}

void test_mixture_distribution_variance() {
    Primary* HB1 = new Primary();
    Primary* HB2 = new Primary();
    HB1->set_scale(1);
    HB2->set_scale(3);
    Mixture<Primary, Primary>* MX = new Mixture<Primary, Primary>(HB1, HB2, 0.5);

    assert(std::abs(MX->variance() - 2.24) < 0.01);

    delete MX;
    std::cout << "test_mixture_distribution_variance passed." << std::endl;
}

void test_late_binding_mechanism() {
    Primary* HB1 = new Primary();
    Primary* HB2 = new Primary();
    HB1->set_scale(1);
    HB2->set_scale(3);

    Mixture<Primary, Primary>* MX1 = new Mixture<Primary, Primary>(HB1, HB2, 0.5);
    Mixture<Primary, Mixture<Primary, Primary>>* MX2 = new Mixture<Primary, Mixture<Primary, Primary>>(HB1, MX1, 0.5);

    assert(std::abs(MX2->get_component1()->get_v() - 1) < 0.01);
    assert(std::abs(MX2->get_component1()->get_shift() - 0) < 0.01);
    assert(std::abs(MX2->get_component1()->get_scale() - 1) < 0.01);
    assert(std::abs(MX2->get_component2()->get_component1()->get_v() - 1) < 0.01);
    assert(std::abs(MX2->get_component2()->get_component1()->get_shift() - 0) < 0.01);
    assert(std::abs(MX2->get_component2()->get_component1()->get_scale() - 1) < 0.01);
    assert(std::abs(MX2->get_component2()->get_component2()->get_v() - 1) < 0.01);
    assert(std::abs(MX2->get_component2()->get_component2()->get_shift() - 0) < 0.01);
    assert(std::abs(MX2->get_component2()->get_component2()->get_scale() - 3) < 0.01);

    delete MX2;
    std::cout << "test_late_binding_mechanism passed." << std::endl;
}

void test_empirical_distribution() {
    Primary* HB1 = new Primary();
    Empirical* EM = new Empirical(HB1, 200, 1);

    assert(EM->get_n() == 200);
    assert(EM->get_k() == 8);

    delete EM;
    std::cout << "test_empirical_distribution passed." << std::endl;
}

int main() {
    test_basic_methods();
    test_standard_distribution();
    test_shift_scale_transformation();
    test_mixture_distribution();
    test_mixture_distribution_expected_value();
    test_mixture_distribution_variance();
    test_late_binding_mechanism();
    test_empirical_distribution();

    std::cout << "All tests passed." << std::endl;
    return 0;
}