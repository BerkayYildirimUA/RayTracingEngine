#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>
#include "Eigen/Core"
#include "iostream"
#include "Math/include/Transformations.h"
#include "Math/include/InverseTransformations.h"

TEST_CASE("Translation", "[Transformations]") {

    Point3 point = Point3(1, 2, 3);

    Eigen::Matrix<double, 4, 1> result = Transformations::translatePoint(point.point, 2, 3, 4);

    Eigen::Matrix<double, 4, 1> expected;
    expected << 3, 5, 7, 1;

    REQUIRE(result.isApprox(expected, 1e-3));
}

TEST_CASE("Scaling", "[Transformations]") {
    Point3 point = Point3(1, 2, 3);

    Eigen::Matrix<double, 4, 1> result = Transformations::scalePoint(point.point, 2, 3, 4);

    Eigen::Matrix<double, 4, 1> expected;
    expected << 2, 6, 12, 1;

    REQUIRE(result.isApprox(expected, 1e-3));
}

TEST_CASE("X-rotation", "[Transformations]") {
    Point3 point = Point3(1, 2, 3);

    double angle = 45;
    Eigen::Matrix<double, 4, 1> result = Transformations::rotatePointX(point.point, angle);

    Eigen::Matrix<double, 4, 1> expected;
    expected << 1, -0.707, 3.536, 1;

    REQUIRE(result.isApprox(expected, 1e-3));
}

TEST_CASE("Y-rotation", "[Transformations][Yroll]") {
    Point3 point = Point3(3, 1, 4);

    Eigen::Matrix<double, 4, 1> result = Transformations::rotatePointY(point.point, 30);

    Eigen::Matrix<double, 4, 1> expected;
    expected << 4.6, 1, 1.964, 1;
    REQUIRE(result.isApprox(expected, 1e-3));
}

TEST_CASE("Z-rotation", "[Transformations]") {
    Point3 point = Point3(1, 2, 3);

    Eigen::Matrix<double, 4, 1> result = Transformations::rotatePointZ(point.point, 60);

    Eigen::Matrix<double, 4, 1> expected;
    expected << -1.232, 1.866, 3, 1;

    REQUIRE(result.isApprox(expected, 1e-3));
}

TEST_CASE("Z-rotation and inverse", "[Transformations]") {
    Point3 point = Point3(1, 2, 3);

    Eigen::Matrix<double, 4, 1> result = Transformations::rotatePointZ(point.point, 60);

    result = InverseTransformations::inverseRotationZ(result, 60);

    Eigen::Matrix<double, 4, 1> expected;
    expected << 1, 2, 3, 1;

    REQUIRE(result.isApprox(expected, 1e-3));
}