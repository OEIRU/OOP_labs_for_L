#include <cassert>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Primary.h"

void test_standard_distribution() {
    double v = 0.5;
    Primary* HB = new Primary(v);
    assert(HB->get_v() == 0.5);
    assert(HB->get_k() == HB->K(v));
    assert(HB->get_scale() == 1.);
    assert(HB->get_shift() == 0.);
    assert(std::abs(HB->f(0) - 0.223) < 0.01);
    assert(std::abs(HB->P() - 0.214) < 0.01);
    assert(HB->expected_value() == HB->get_shift());
    assert(std::abs(HB->variance() - 8.08) < 0.01);
    assert(HB->asymmetry() == 0.);
    assert(std::abs(HB->kurtosis() - 2.94) < 0.01);

    v = 0.75;
    HB->set_v(v);
    assert(HB->get_v() == 0.75);
    assert(HB->get_k() == HB->K(v));
    assert(HB->get_scale() == 1.);
    assert(HB->get_shift() == 0.);
    assert(std::abs(HB->f(0) - 0.296) < 0.01);
    assert(std::abs(HB->P() - 0.405) < 0.01);
    assert(HB->expected_value() == HB->get_shift());
    assert(std::abs(HB->variance() - 3.71) < 0.01);
    assert(HB->asymmetry() == 0.);
    assert(std::abs(HB->kurtosis() - 2.75) < 0.01);

    v = 1;
    HB->set_v(v);
    assert(HB->get_v() == 1.);
    assert(HB->get_k() == HB->K(v));
    assert(HB->get_scale() == 1.);
    assert(HB->get_shift() == 0.);
    assert(std::abs(HB->f(0) - 0.342) < 0.01);
    assert(std::abs(HB->P() - 0.585) < 0.01);
    assert(HB->expected_value() == HB->get_shift());
    assert(std::abs(HB->variance() - 2.24) < 0.01);
    assert(HB->asymmetry() == 0.);
    assert(std::abs(HB->kurtosis() - 2.37) < 0.01);

    v = 1.5;
    HB->set_v(v);
    assert(HB->get_v() == 1.5);
    assert(HB->get_k() == HB->K(v));
    assert(HB->get_scale() == 1.);
    assert(HB->get_shift() == 0.);
    assert(std::abs(HB->f(0) - 0.384) < 0.01);
    assert(std::abs(HB->P() - 0.834) < 0.01);
    assert(HB->expected_value() == HB->get_shift());
    assert(std::abs(HB->variance() - 1.31) < 0.01);
    assert(HB->asymmetry() == 0.);
    assert(std::abs(HB->kurtosis() - 1.30) < 0.01);

    v = 2;
    HB->set_v(v);
    assert(HB->get_v() == 2.);
    assert(HB->get_k() == HB->K(v));
    assert(HB->get_scale() == 1.);
    assert(HB->get_shift() == 0.);
    assert(std::abs(HB->f(0) - 0.396) < 0.01);
    assert(std::abs(HB->P() - 0.946) < 0.01);
    assert(HB->expected_value() == HB->get_shift());
    assert(std::abs(HB->variance() - 1.08) < 0.01);
    assert(HB->asymmetry() == 0.);
    assert(std::abs(HB->kurtosis() - 0.51) < 0.01);

    v = 2.5;
    HB->set_v(v);
    assert(HB->get_v() == 2.5);
    assert(HB->get_k() == HB->K(v));
    assert(HB->get_scale() == 1.);
    assert(HB->get_shift() == 0.);
    assert(std::abs(HB->f(0) - 0.398) < 0.01);
    assert(std::abs(HB->P() - 0.986) < 0.01);
    assert(HB->expected_value() == HB->get_shift());
    assert(std::abs(HB->variance() - 1.02) < 0.01);
    assert(HB->asymmetry() == 0.);
    assert(std::abs(HB->kurtosis() - 0.16) < 0.1);

    v = 3;
    HB->set_v(v);
    assert(HB->get_v() == 3.);
    assert(HB->get_k() == HB->K(v));
    assert(HB->get_scale() == 1.);
    assert(HB->get_shift() == 0.);
    assert(std::abs(HB->f(0) - 0.399) < 0.01);
    assert(std::abs(HB->P() - 0.997) < 0.01);
    assert(HB->expected_value() == HB->get_shift());
    assert(std::abs(HB->variance() - 1.00) < 0.01);
    assert(HB->asymmetry() == 0.);
    assert(std::abs(HB->kurtosis() - 0.04) < 0.01);

    delete HB;
    std::cout << "test_standard_distribution passed." << std::endl;
}

void test_scaled_and_shifted_distribution() {
    double v = 1.5;
    double scale = 2;
    double shift = 5;
    Primary* HB = new Primary(v, scale, shift);
    assert(HB->get_v() == 1.5);
    assert(HB->get_scale() == 2.);
    assert(HB->get_shift() == 5.);
    assert(HB->expected_value() == HB->get_shift());
    assert(std::abs(HB->variance() - 1.31) < 0.01);
    assert(HB->asymmetry() == 0.);
    assert(std::abs(HB->kurtosis() - 1.30) < 0.01);

    v = 3.;
    scale = 0.5;
    shift = 1;
    HB->set_v(v);
    HB->set_scale(scale);
    HB->set_shift(shift);
    assert(HB->get_v() == 3.);
    assert(HB->get_scale() == 0.5);
    assert(HB->get_shift() == 1.);
    assert(HB->expected_value() == HB->get_shift());
    assert(std::abs(HB->variance() - 1.00) < 0.01);
    assert(HB->asymmetry() == 0.);
    assert(std::abs(HB->kurtosis() - 0.04) < 0.01);

    delete HB;
    std::cout << "test_scaled_and_shifted_distribution passed." << std::endl;
}

void test_error_processing() {
    std::ifstream file;
    bool exceptionThrown = false;

    try {
        new Primary(-1);
    } catch (const std::invalid_argument&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    exceptionThrown = false;
    try {
        new Primary(5, 0, 0);
    } catch (const std::invalid_argument&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    exceptionThrown = false;
    try {
        new Primary(file);
    } catch (const std::runtime_error&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    std::cout << "test_error_processing passed." << std::endl;
}

int main() {
    test_standard_distribution();
    test_scaled_and_shifted_distribution();
    test_error_processing();

    std::cout << "All tests passed." << std::endl;
    return 0;
}