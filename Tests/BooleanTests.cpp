//
// Created by berka on 26/11/2024.
//
#include <catch2/catch_all.hpp>
#include "Eigen/Core"
#include "Intersection.h"
#include "ObjectFactory.h"

TEST_CASE("Union", "[Union]") {
    std::shared_ptr<AbstractMaterial> material1 = std::make_shared<FresnelMaterial>(1, 0, 0, 0.4, 0.4, 0.2);

    auto cube = ObjectFactory::createObject<UnitCube>(material1);
    auto sphere = ObjectFactory::createObject<UnitSphere>(material1);

    auto theUnion = ObjectFactory::createBoolObject<UnionBool>(cube, sphere);


    Intersection A;
    A.getHit(0)->hitTime = 1.2;
    A.getHit(1)->hitTime = 1.5;
    A.getHit(2)->hitTime = 2.1;
    A.getHit(3)->hitTime = 2.5;
    A.getHit(4)->hitTime = 3.1;
    A.getHit(5)->hitTime = 3.8;

    for (int i = 0; i < 6; i += 2) {
        A.getHit(i)->isEntering = true;
    }

    Intersection B;
    B.getHit(0)->hitTime = 0.6;
    B.getHit(1)->hitTime = 1.1;
    B.getHit(2)->hitTime = 1.8;
    B.getHit(3)->hitTime = 2.6;
    B.getHit(4)->hitTime = 3.4;
    B.getHit(5)->hitTime = 4.0;

    for (int i = 0; i < 6; i += 2) {
        B.getHit(i)->isEntering = true;
    }

    auto C = theUnion->useOperation(A, B);

    REQUIRE(C.getHit(0)->hitTime == 0.6);


}

TEST_CASE("Intersection", "[Intersection]") {
    std::shared_ptr<AbstractMaterial> material1 = std::make_shared<FresnelMaterial>(1, 0, 0, 0.4, 0.4, 0.2);

    auto cube = ObjectFactory::createObject<UnitCube>(material1);
    auto sphere = ObjectFactory::createObject<UnitSphere>(material1);

    auto theUnion = ObjectFactory::createBoolObject<IntersectionBool>(cube, sphere);


    Intersection A;
    A.getHit(0)->hitTime = 1.2;
    A.getHit(1)->hitTime = 1.5;
    A.getHit(2)->hitTime = 2.1;
    A.getHit(3)->hitTime = 2.5;
    A.getHit(4)->hitTime = 3.1;
    A.getHit(5)->hitTime = 3.8;

    for (int i = 0; i < 6; i += 2) {
        A.getHit(i)->isEntering = true;
    }

    Intersection B;
    B.getHit(0)->hitTime = 0.6;
    B.getHit(1)->hitTime = 1.1;
    B.getHit(2)->hitTime = 1.8;
    B.getHit(3)->hitTime = 2.6;
    B.getHit(4)->hitTime = 3.4;
    B.getHit(5)->hitTime = 4.0;

    for (int i = 0; i < 6; i += 2) {
        B.getHit(i)->isEntering = true;
    }

    auto C = theUnion->useOperation(A, B);

    REQUIRE(C.getHit(0)->hitTime == 2.1);
}

TEST_CASE("Difference, A - B", "[Difference]") {
    std::shared_ptr<AbstractMaterial> material1 = std::make_shared<FresnelMaterial>(1, 0, 0, 0.4, 0.4, 0.2);

    auto cube = ObjectFactory::createObject<UnitCube>(material1);
    auto sphere = ObjectFactory::createObject<UnitSphere>(material1);

    auto theUnion = ObjectFactory::createBoolObject<DifferenceBool>(cube, sphere);


    Intersection A;
    A.getHit(0)->hitTime = 1.2;
    A.getHit(1)->hitTime = 1.5;
    A.getHit(2)->hitTime = 2.1;
    A.getHit(3)->hitTime = 2.5;
    A.getHit(4)->hitTime = 3.1;
    A.getHit(5)->hitTime = 3.8;

    for (int i = 0; i < 6; i += 2) {
        A.getHit(i)->isEntering = true;
    }

    Intersection B;
    B.getHit(0)->hitTime = 0.6;
    B.getHit(1)->hitTime = 1.1;
    B.getHit(2)->hitTime = 1.8;
    B.getHit(3)->hitTime = 2.6;
    B.getHit(4)->hitTime = 3.4;
    B.getHit(5)->hitTime = 4.0;

    for (int i = 0; i < 6; i += 2) {
        B.getHit(i)->isEntering = true;
    }

    auto C = theUnion->useOperation(A, B);

    REQUIRE(C.getHit(0)->hitTime == 1.2);
}

TEST_CASE("Difference, B - A", "[Difference]") {
    std::shared_ptr<AbstractMaterial> material1 = std::make_shared<FresnelMaterial>(1, 0, 0, 0.4, 0.4, 0.2);

    auto cube = ObjectFactory::createObject<UnitCube>(material1);
    auto sphere = ObjectFactory::createObject<UnitSphere>(material1);

    auto theUnion = ObjectFactory::createBoolObject<DifferenceBool>(cube, sphere);


    Intersection A;
    A.getHit(0)->hitTime = 1.2;
    A.getHit(1)->hitTime = 1.5;
    A.getHit(2)->hitTime = 2.1;
    A.getHit(3)->hitTime = 2.5;
    A.getHit(4)->hitTime = 3.1;
    A.getHit(5)->hitTime = 3.8;

    for (int i = 0; i < 6; i += 2) {
        A.getHit(i)->isEntering = true;
    }

    Intersection B;
    B.getHit(0)->hitTime = 0.6;
    B.getHit(1)->hitTime = 1.1;
    B.getHit(2)->hitTime = 1.8;
    B.getHit(3)->hitTime = 2.6;
    B.getHit(4)->hitTime = 3.4;
    B.getHit(5)->hitTime = 4.0;

    for (int i = 0; i < 6; i += 2) {
        B.getHit(i)->isEntering = true;
    }

    auto C = theUnion->useOperation(B, A);

    REQUIRE(C.getHit(0)->hitTime == 0.6);
}