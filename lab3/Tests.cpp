#include "Primary.h"
#include "Mixture.h"
#include "Empirical.h"
#include "catch.hpp"


TEST_CASE("Basic Methods")
{
    Primary* HB = new Primary();
    CHECK(HB->get_v() == Approx(1.).epsilon(0.01));
    CHECK(HB->get_shift() == Approx(0.).epsilon(0.01));
    CHECK(HB->get_scale() == Approx(1.).epsilon(0.01));
}

TEST_CASE("Standard Distribution")
{
    Primary* HB = new Primary();
    CHECK(HB->f(0) == Approx(0.341).epsilon(0.01));
    CHECK(HB->expected_value() == Approx(0).epsilon(0.01));
    CHECK(HB->variance() == Approx(2.24).epsilon(0.01));
    CHECK(HB->asymmetry() == Approx(0).epsilon(0.01));
    CHECK(HB->kurtosis() == Approx(2.37).epsilon(0.01));
}

TEST_CASE("Primary; Shift and Scaled")
{
    Primary* HB = new Primary();
    HB->set_scale(2);
    HB->set_shift(2);
    CHECK(HB->f(0) == Approx(0.103).epsilon(0.01));
    CHECK(HB->expected_value() == Approx(2).epsilon(0.01));
    CHECK(HB->variance() == Approx(2.24).epsilon(0.01));
    CHECK(HB->asymmetry() == Approx(0).epsilon(0.01));
    CHECK(HB->kurtosis() == Approx(2.37).epsilon(0.01));
}

TEST_CASE("Mixture of Distributions")
{
    Mixture* MX = new Mixture();
    MX->get_component1()->set_scale(2);
    MX->get_component2()->set_scale(2);
    MX->get_component1()->set_shift(2);
    MX->get_component2()->set_shift(2);
    CHECK(MX->f(0) == Approx(0.103).epsilon(0.01));
    CHECK(MX->expected_value() == Approx(2).epsilon(0.01));
    CHECK(MX->variance() == Approx(2.24).epsilon(0.01));
    CHECK(MX->asymmetry() == Approx(0).epsilon(0.01));
    CHECK(MX->kurtosis() == Approx(1.77).epsilon(0.01));
}

TEST_CASE("Mixture Distribution - Expected value test")
{
    Mixture* MX = new Mixture();
    MX->get_component1()->set_scale(2);
    MX->get_component2()->set_scale(2);
    MX->get_component1()->set_shift(1);
    MX->get_component2()->set_shift(2);
    CHECK(MX->expected_value() == Approx(1.5).epsilon(0.01));
}

TEST_CASE("Mixture Distribution - Variance test")
{
    Mixture* MX = new Mixture();
    MX->get_component1()->set_scale(1);
    MX->get_component2()->set_scale(3);
    CHECK(MX->variance() == Approx(2.24).epsilon(0.01));
}