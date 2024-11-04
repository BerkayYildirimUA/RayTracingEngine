//
// Created by berka on 03/11/2024.
//
#include <catch2/catch_all.hpp>
#include "Math/include/GeometricFunctionsLookup.h"

TEST_CASE("Testing cosine lookup accuracy", "[Cos]") {
    const double tolerance = 1e-6; // Define an acceptable tolerance level

    for(double angle = -2 * EIGEN_PI; angle <= 2 * EIGEN_PI; angle += 0.001) {
        double expected = std::cos(angle);
        double result = GeometricFunctionsLookup::getCos(angle);

        REQUIRE(std::abs(expected - result) < tolerance);
    }

}


TEST_CASE("Testing arccosine lookup accuracy", "[ACos]") {
    const double tolerance = 1e-6;

    for(double i = -1; i <= 1; i += 0.001) {
        double expected = std::acos(i);
        double result = GeometricFunctionsLookup::getAcos(i);

        REQUIRE(std::abs(expected - result) < tolerance);
    }

}

