//
// Created by berka on 15/10/2024.
//

#include <catch2/catch_all.hpp>
#include "Eigen/Core"
#include "iostream"
#include "Math/include/Transformations.h"
#include "Math/include/InverseTransformations.h"
#include "Math/include/TransformationManager.h"
#include "Geometry/include/unitGeometricObjects/UnitCircle.h"
#include "Geometry/include/ObjectFactory.h"
#include "memory"
#include "Geometry/include/unitGeometricObjects/UnitCube.h"
#include "Shaders/Material/FresnelMaterial.h"


TEST_CASE("test circle hit book page 620", "[Circle]") {

    std::shared_ptr<AbstractMaterial> material = std::make_shared<FresnelMaterial>(0, 0, 0, 0,0, 0);

    std::shared_ptr<HitObject> circle = ObjectFactory::createObject<UnitSphere>(material);

    Intersection intersection;
    Point3 point3(3, 2, 3);
    Vector3 dir(-3, -2, -3);


    Ray ray(std::move(point3), std::move(dir));

    REQUIRE(circle->hit(ray, intersection));

    REQUIRE(intersection.numHits == 2);

    REQUIRE_THAT(intersection.getHits(0)->hitTime, Catch::Matchers::WithinRel(0.7868, 0.001));
    REQUIRE_THAT(intersection.getHits(1)->hitTime, Catch::Matchers::WithinRel(1.2132, 0.001));

    REQUIRE(intersection.getHits(0)->isEntering);
    REQUIRE(!intersection.getHits(1)->isEntering);

    Point3 enteringPoint(0.6393, 0.4264, 0.6396);
    Point3 exitPoint(-0.6393, -0.4264, -0.6396);

    REQUIRE(enteringPoint.point.isApprox(intersection.getHits(0)->hitPoint.point, 0.001));
    REQUIRE(exitPoint.point.isApprox(intersection.getHits(1)->hitPoint.point, 0.001));

}

TEST_CASE("test circle hit", "[Circle]") {
    std::shared_ptr<AbstractMaterial> material = std::make_shared<FresnelMaterial>(0, 0, 0, 0,0, 0);

    std::shared_ptr<HitObject> circle = ObjectFactory::createObject<UnitSphere>(material);

    Intersection intersection;
    Point3 point3(4, 4, 5);
    Vector3 dir(-1, -1, -1);


    Ray ray(std::move(point3), std::move(dir));

    REQUIRE(circle->hit(ray, intersection));

    REQUIRE(intersection.numHits == 2);

    REQUIRE_THAT(intersection.getHits(0)->hitTime, Catch::Matchers::WithinRel(4, 0.001));
    REQUIRE_THAT(intersection.getHits(1)->hitTime, Catch::Matchers::WithinRel(14.0/3.0, 0.001));

    REQUIRE(intersection.getHits(0)->isEntering);
    REQUIRE(!intersection.getHits(1)->isEntering);

    Point3 enteringPoint(0, 0, 1);
    Point3 exitPoint(-2.0/3, -2.0/3, 1.0/3);

    REQUIRE(enteringPoint.point.isApprox(intersection.getHits(0)->hitPoint.point, 0.001));
    REQUIRE(exitPoint.point.isApprox(intersection.getHits(1)->hitPoint.point, 0.001));

}

TEST_CASE("test circle hit sides", "[Circle]") {
    std::shared_ptr<AbstractMaterial> material = std::make_shared<FresnelMaterial>(0, 0, 0, 0,0, 0);

    std::shared_ptr<HitObject> circle = ObjectFactory::createObject<UnitSphere>(material);

    Intersection intersection;
    Point3 point3(1, 1, 0);
    Vector3 dir(-1, 0, 0);


    Ray ray(std::move(point3), std::move(dir));

    REQUIRE(circle->hit(ray, intersection));

    REQUIRE(intersection.numHits == 1);
    REQUIRE(intersection.isNull(1));

    REQUIRE_THAT(intersection.getHits(0)->hitTime, Catch::Matchers::WithinRel(1, 0.001));

    REQUIRE(intersection.getHits(0)->isEntering);

    Point3 point(0, 1, 0);

    REQUIRE(point.point.isApprox(intersection.getHits(0)->hitPoint.point, 0.001));
}

TEST_CASE("test cube hit side", "[Cube]") {
    std::shared_ptr<AbstractMaterial> material = std::make_shared<FresnelMaterial>(0, 0, 0, 0,0, 0);

    std::shared_ptr<HitObject> cube = ObjectFactory::createObject<UnitCube>(material);

    Intersection intersection;
    Point3 point3(0, 1, 2);
    Vector3 dir(-0.5, -0.75, -1);


    Ray ray(std::move(point3), std::move(dir));

    REQUIRE(cube->hit(ray, intersection));

    REQUIRE(intersection.numHits == 2);
    REQUIRE(intersection.getHits(0)->isEntering);
    REQUIRE(!intersection.getHits(1)->isEntering);

    REQUIRE(intersection.getHits(0)->hitPoint.point.isApprox(Point3(-0.5, 0.25, 1).point, 0.001));
    REQUIRE(intersection.getHits(1)->hitPoint.point.isApprox(Point3(-1, -0.5, 0).point, 0.001));
}

TEST_CASE("test cube hit edge", "[Cube]") {
    std::shared_ptr<AbstractMaterial> material = std::make_shared<FresnelMaterial>(0, 0, 0, 0,0, 0);

    std::shared_ptr<HitObject> cube = ObjectFactory::createObject<UnitCube>(material);

    Intersection intersection;
    Point3 point3(5, 1, 1);
    Vector3 dir(-2, 0, 0);


    Ray ray(std::move(point3), std::move(dir));

    REQUIRE(cube->hit(ray, intersection));

    REQUIRE(intersection.numHits == 2);
    REQUIRE(intersection.getHits(0)->isEntering);
    REQUIRE(!intersection.getHits(1)->isEntering);

    REQUIRE(intersection.getHits(0)->hitPoint.point.isApprox(Point3(1, 1, 1).point, 0.001));
    REQUIRE(intersection.getHits(1)->hitPoint.point.isApprox(Point3(-1, 1, 1).point, 0.001));
}

TEST_CASE("test cube visual bug", "[Cube]") {
    std::shared_ptr<AbstractMaterial> material = std::make_shared<FresnelMaterial>(0, 0, 0, 0,0, 0);

    std::shared_ptr<HitObject> cube = ObjectFactory::createObject<UnitCube>(material);

    Intersection intersection;
    Point3 point3(-1.2, -1.1, -5);
    Vector3 dir(0.04, 0.02, 1);


    Ray ray(std::move(point3), std::move(dir));

    REQUIRE(cube->hit(ray, intersection));

    REQUIRE(intersection.numHits == 2);
    REQUIRE(intersection.getHits(0)->isEntering);
    REQUIRE(!intersection.getHits(1)->isEntering);

    REQUIRE((cube->getTransform() * intersection.getHits(0)->hitPoint.point).isApprox(Point3(-1, -1, 0).point, 0.001));
    REQUIRE((cube->getTransform() * intersection.getHits(1)->hitPoint.point).isApprox(Point3(-0.96, -0.98, 1).point, 0.001));
}