//
// Created by berka on 15/10/2024.
//

#include <catch2/catch_all.hpp>
#include "Eigen/Core"
#include "iostream"
#include "Math/include/Transformations.h"
#include "Math/include/InverseTransformations.h"
#include "Geometry/include/unitGeometricObjects/creation/TransformationManager.h"
#include "Geometry/include/unitGeometricObjects/UnitCircle.h"
#include "Geometry/include/unitGeometricObjects/creation/ObjectFactory.h"
#include "memory"

TEST_CASE("test circle hit book page 620", "[Circle]") {

    std::shared_ptr<HitObject> circle = ObjectFactory::createObject<UnitCircle>();

    Intersection intersection;
    Point3 point3(3, 2, 3);
    Vector3 dir(-3, -2, -3);


    Ray ray(std::move(point3), std::move(dir));

    REQUIRE(circle->hit(ray, intersection));

    REQUIRE(intersection.numHits == 2);

    REQUIRE_THAT(intersection.hits[0]->hitTime, Catch::Matchers::WithinRel(0.7868, 0.001));
    REQUIRE_THAT(intersection.hits[1]->hitTime, Catch::Matchers::WithinRel(1.2132, 0.001));

    REQUIRE(intersection.hits[0]->isEntering);
    REQUIRE(!intersection.hits[1]->isEntering);

    Point3 enteringPoint(0.6393, 0.4264, 0.6396);
    Point3 exitPoint(-0.6393, -0.4264, -0.6396);

    REQUIRE(enteringPoint.point.isApprox(intersection.hits[0]->hitPoint.point, 0.001));
    REQUIRE(exitPoint.point.isApprox(intersection.hits[1]->hitPoint.point, 0.001));

}

TEST_CASE("test circle hit", "[Circle]") {

    std::shared_ptr<HitObject> circle = ObjectFactory::createObject<UnitCircle>();

    Intersection intersection;
    Point3 point3(4, 4, 5);
    Vector3 dir(-1, -1, -1);


    Ray ray(std::move(point3), std::move(dir));

    REQUIRE(circle->hit(ray, intersection));

    REQUIRE(intersection.numHits == 2);

    REQUIRE_THAT(intersection.hits[0]->hitTime, Catch::Matchers::WithinRel(4, 0.001));
    REQUIRE_THAT(intersection.hits[1]->hitTime, Catch::Matchers::WithinRel(14.0/3.0, 0.001));

    REQUIRE(intersection.hits[0]->isEntering);
    REQUIRE(!intersection.hits[1]->isEntering);

    Point3 enteringPoint(0, 0, 1);
    Point3 exitPoint(-2.0/3, -2.0/3, 1.0/3);

    REQUIRE(enteringPoint.point.isApprox(intersection.hits[0]->hitPoint.point, 0.001));
    REQUIRE(exitPoint.point.isApprox(intersection.hits[1]->hitPoint.point, 0.001));

}

TEST_CASE("test circle hit edge", "[Circle]") {

    std::shared_ptr<HitObject> circle = ObjectFactory::createObject<UnitCircle>();

    Intersection intersection;
    Point3 point3(1, 1, 0);
    Vector3 dir(-1, 0, 0);


    Ray ray(std::move(point3), std::move(dir));

    REQUIRE(circle->hit(ray, intersection));

    REQUIRE(intersection.numHits == 1);
    REQUIRE(intersection.hits[1].get() == nullptr);

    REQUIRE_THAT(intersection.hits[0]->hitTime, Catch::Matchers::WithinRel(1, 0.001));

    REQUIRE(intersection.hits[0]->isEntering);

    Point3 point(0, 1, 0);

    REQUIRE(point.point.isApprox(intersection.hits[0]->hitPoint.point, 0.001));
}