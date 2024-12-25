#include "catch.hpp"
#include "Primary.h"

TEST_CASE("standard distribution") {

    double v = 0.5;
    Primary* HB = new Primary(v);
    REQUIRE(HB->get_v() == 0.5);
    REQUIRE(HB->get_k() == HB->K(v));
    REQUIRE(HB->get_scale() == 1.);
    REQUIRE(HB->get_shift() == 0.);
    REQUIRE(HB->f(0) == Approx(0.223).epsilon(0.01));
    REQUIRE(HB->P() == Approx(0.214).epsilon(0.01));
    REQUIRE(HB->expected_value() == HB->get_shift());
    REQUIRE(HB->variance() == Approx(8.08).epsilon(0.01));
    REQUIRE(HB->asymmetry() == 0.);
    REQUIRE(HB->kurtosis() == Approx(2.94).epsilon(0.01));

    v = 0.75;
    HB->set_v(v);
    REQUIRE(HB->get_v() == 0.75);
    REQUIRE(HB->get_k() == HB->K(v));
    REQUIRE(HB->get_scale() == 1.);
    REQUIRE(HB->get_shift() == 0.);
    REQUIRE(HB->f(0) == Approx(0.296).epsilon(0.01));
    REQUIRE(HB->P() == Approx(0.405).epsilon(0.01));
    REQUIRE(HB->expected_value() == HB->get_shift());
    REQUIRE(HB->variance() == Approx(3.71).epsilon(0.01));
    REQUIRE(HB->asymmetry() == 0.);
    REQUIRE(HB->kurtosis() == Approx(2.75).epsilon(0.01));

    v = 1;
    HB->set_v(v);
    REQUIRE(HB->get_v() == 1.);
    REQUIRE(HB->get_k() == HB->K(v));
    REQUIRE(HB->get_scale() == 1.);
    REQUIRE(HB->get_shift() == 0.);
    REQUIRE(HB->f(0) == Approx(0.342).epsilon(0.01));
    REQUIRE(HB->P() == Approx(0.585).epsilon(0.01));
    REQUIRE(HB->expected_value() == HB->get_shift());
    REQUIRE(HB->variance() == Approx(2.24).epsilon(0.01));
    REQUIRE(HB->asymmetry() == 0.);
    REQUIRE(HB->kurtosis() == Approx(2.37).epsilon(0.01));

    v = 1.5;
    HB->set_v(v);
    REQUIRE(HB->get_v() == 1.5);
    REQUIRE(HB->get_k() == HB->K(v));
    REQUIRE(HB->get_scale() == 1.);
    REQUIRE(HB->get_shift() == 0.);
    REQUIRE(HB->f(0) == Approx(0.384).epsilon(0.01));
    REQUIRE(HB->P() == Approx(0.834).epsilon(0.01));
    REQUIRE(HB->expected_value() == HB->get_shift());
    REQUIRE(HB->variance() == Approx(1.31).epsilon(0.01));
    REQUIRE(HB->asymmetry() == 0.);
    REQUIRE(HB->kurtosis() == Approx(1.30).epsilon(0.01));

    v = 2;
    HB->set_v(v);
    REQUIRE(HB->get_v() == 2.);
    REQUIRE(HB->get_k() == HB->K(v));
    REQUIRE(HB->get_scale() == 1.);
    REQUIRE(HB->get_shift() == 0.);
    REQUIRE(HB->f(0) == Approx(0.396).epsilon(0.01));
    REQUIRE(HB->P() == Approx(0.946).epsilon(0.01));
    REQUIRE(HB->expected_value() == HB->get_shift());
    REQUIRE(HB->variance() == Approx(1.08).epsilon(0.01));
    REQUIRE(HB->asymmetry() == 0.);
    REQUIRE(HB->kurtosis() == Approx(0.51).epsilon(0.01));

    v = 2.5;
    HB->set_v(v);
    REQUIRE(HB->get_v() == 2.5);
    REQUIRE(HB->get_k() == HB->K(v));
    REQUIRE(HB->get_scale() == 1.);
    REQUIRE(HB->get_shift() == 0.);
    REQUIRE(HB->f(0) == Approx(0.398).epsilon(0.01));
    REQUIRE(HB->P() == Approx(0.986).epsilon(0.01));
    REQUIRE(HB->expected_value() == HB->get_shift());
    REQUIRE(HB->variance() == Approx(1.02).epsilon(0.01));
    REQUIRE(HB->asymmetry() == 0.);
    REQUIRE(HB->kurtosis() == Approx(0.16).epsilon(0.1));

    v = 3;
    HB->set_v(v);
    REQUIRE(HB->get_v() == 3.);
    REQUIRE(HB->get_k() == HB->K(v));
    REQUIRE(HB->get_scale() == 1.);
    REQUIRE(HB->get_shift() == 0.);
    REQUIRE(HB->f(0) == Approx(0.399).epsilon(0.01));
    REQUIRE(HB->P() == Approx(0.997).epsilon(0.01));
    REQUIRE(HB->expected_value() == HB->get_shift());
    REQUIRE(HB->variance() == Approx(1.00).epsilon(0.01));
    REQUIRE(HB->asymmetry() == 0.);
    REQUIRE(HB->kurtosis() == Approx(0.04).epsilon(0.01));
}


TEST_CASE("Scaled and shifted distribution") {

    double v = 1.5;
    double scale = 2;
    double shift = 5;
    Primary* HB = new Primary(v, scale, shift);
    REQUIRE(HB->get_v() == 1.5);
    REQUIRE(HB->get_scale() == 2.);
    REQUIRE(HB->get_shift() == 5.);
    REQUIRE(HB->expected_value() == HB->get_shift());
    REQUIRE(HB->variance() == Approx(1.31).epsilon(0.01));
    REQUIRE(HB->asymmetry() == 0.);
    REQUIRE(HB->kurtosis() == Approx(1.30).epsilon(0.01));

	v = 3.;
    scale = 0.5;
    shift = 1;
    HB->set_v(v);
    HB->set_scale(scale);
    HB->set_shift(shift);
    REQUIRE(HB->get_v() == 3.);
    REQUIRE(HB->get_scale() == 0.5);
    REQUIRE(HB->get_shift() == 1.);
    REQUIRE(HB->expected_value() == HB->get_shift());
    REQUIRE(HB->variance() == Approx(1.00).epsilon(0.01));
    REQUIRE(HB->asymmetry() == 0.);
    REQUIRE(HB->kurtosis() == Approx(0.04).epsilon(0.01));
}

TEST_CASE("Error processing")
{
    ifstream file;
    REQUIRE_THROWS_AS(new Primary(-1), invalid_argument);
    REQUIRE_THROWS_AS(new Primary(5, 0, 0), invalid_argument);
    REQUIRE_THROWS_AS(new Primary(file), runtime_error);
}