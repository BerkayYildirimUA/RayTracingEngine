//
// Created by berka on 15/10/2024.
//

#include <catch2/catch_all.hpp>
#include "Eigen/Core"
#include "iostream"
#include "Math/include/Transformations.h"
#include "Math/include/InverseTransformations.h"
#include "Math/include/TransformationManager.h"
#include "Geometry/include/unitGeometricObjects/UnitSphere.h"
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

    REQUIRE_THAT(intersection.getHit(0)->hitTime, Catch::Matchers::WithinRel(0.7868, 0.001));
    REQUIRE_THAT(intersection.getHit(1)->hitTime, Catch::Matchers::WithinRel(1.2132, 0.001));

    REQUIRE(intersection.getHit(0)->isEntering);
    REQUIRE(!intersection.getHit(1)->isEntering);

    Point3 enteringPoint(0.6393, 0.4264, 0.6396);
    Point3 exitPoint(-0.6393, -0.4264, -0.6396);

    REQUIRE(enteringPoint.point.isApprox(intersection.getHit(0)->hitPoint.point, 0.001));
    REQUIRE(exitPoint.point.isApprox(intersection.getHit(1)->hitPoint.point, 0.001));

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

    REQUIRE_THAT(intersection.getHit(0)->hitTime, Catch::Matchers::WithinRel(4, 0.001));
    REQUIRE_THAT(intersection.getHit(1)->hitTime, Catch::Matchers::WithinRel(14.0 / 3.0, 0.001));

    REQUIRE(intersection.getHit(0)->isEntering);
    REQUIRE(!intersection.getHit(1)->isEntering);

    Point3 enteringPoint(0, 0, 1);
    Point3 exitPoint(-2.0/3, -2.0/3, 1.0/3);

    REQUIRE(enteringPoint.point.isApprox(intersection.getHit(0)->hitPoint.point, 0.001));
    REQUIRE(exitPoint.point.isApprox(intersection.getHit(1)->hitPoint.point, 0.001));

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

    REQUIRE_THAT(intersection.getHit(0)->hitTime, Catch::Matchers::WithinRel(1, 0.001));

    REQUIRE(intersection.getHit(0)->isEntering);

    Point3 point(0, 1, 0);

    REQUIRE(point.point.isApprox(intersection.getHit(0)->hitPoint.point, 0.001));
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
    REQUIRE(intersection.getHit(0)->isEntering);
    REQUIRE(!intersection.getHit(1)->isEntering);

    REQUIRE(intersection.getHit(0)->hitPoint.point.isApprox(Point3(-0.5, 0.25, 1).point, 0.001));
    REQUIRE(intersection.getHit(1)->hitPoint.point.isApprox(Point3(-1, -0.5, 0).point, 0.001));
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
    REQUIRE(intersection.getHit(0)->isEntering);
    REQUIRE(!intersection.getHit(1)->isEntering);

    REQUIRE(intersection.getHit(0)->hitPoint.point.isApprox(Point3(1, 1, 1).point, 0.001));
    REQUIRE(intersection.getHit(1)->hitPoint.point.isApprox(Point3(-1, 1, 1).point, 0.001));
}

TEST_CASE("test cube visual bug", "[Cube]") {
    std::shared_ptr<AbstractMaterial> material = std::make_shared<FresnelMaterial>(0, 0, 0, 0,0, 0);

    std::shared_ptr<PrimitiveObjects> cube = ObjectFactory::createObject<UnitCube>(material);

    Intersection intersection;
    Point3 point3(-1.2, -1.1, -5);
    Vector3 dir(0.04, 0.02, 1);


    Ray ray(std::move(point3), std::move(dir));

    REQUIRE(cube->hit(ray, intersection));

    REQUIRE(intersection.numHits == 2);
    REQUIRE(intersection.getHit(0)->isEntering);
    REQUIRE(!intersection.getHit(1)->isEntering);

    REQUIRE((cube->getTransform() * intersection.getHit(0)->hitPoint.point).isApprox(Point3(-1, -1, 0).point, 0.001));
    REQUIRE((cube->getTransform() * intersection.getHit(1)->hitPoint.point).isApprox(Point3(-0.96, -0.98, 1).point, 0.001));
}

TEST_CASE("test normal of circle", "[Sphere]") {
    std::shared_ptr<AbstractMaterial> material = std::make_shared<FresnelMaterial>(0, 0, 0, 0,0, 0);

    TransformationManager manger;
    manger.pushTranslation(0, 0, 10);
    manger.pushScale(1, 8, 2);
    manger.pushRotatePointY(180);
    manger.pushRotatePointZ(29); // --> x^2 + 0.02y^2 + 0.25z^2 - 5z = -24


    std::shared_ptr<PrimitiveObjects> sphere = ObjectFactory::createObject<UnitSphere>(manger, material);

    Intersection intersection;
    Point3 point3(4, 5, 16);
    Vector3 dir(-4, -5, -6);


    Ray ray(std::move(point3), std::move(dir));

    REQUIRE(sphere->hit(ray, intersection));

    //std::cout << intersection.getHit(0)->hitNormal.vector << std::endl << std::endl;

    std::cout << sphere->getTransform() * intersection.getHit(0)->hitPoint.point << std::endl << std::endl;
    std::cout << sphere->getTransform() * intersection.getHit(1)->hitPoint.point << std::endl << std::endl;

    std::cout << ray.calcPoint(intersection.getHit(0)->hitTime) << std::endl << std::endl;
    std::cout << ray.calcPoint(intersection.getHit(1)->hitTime) << std::endl << std::endl;


    //std::cout << "--------------------- affine (4x4) matrixes --------------------- " << "\n";
    //std::cout << "transform: \n"                      << (intersection.getHits(0)->hitObject->getTransform() * intersection.getHit(0)->hitNormal.vector).normalized() << std::endl << std::endl;
    //std::cout << "transform and transpose: \n"        << (intersection.getHit(0)->hitObject->getTransform().transpose() * intersection.getHits(0)->hitNormal.vector).normalized() << std::endl << std::endl;
    //std::cout << "inversetransform: \n"               << (intersection.getHit(0)->hitObject->getInverseTransform() * intersection.getHits(0)->hitNormal.vector).normalized() << std::endl << std::endl;
    //std::cout << "inversetransform and transpose: \n" << (intersection.getHits(0)->hitObject->getInverseTransform().transpose() * intersection.getHit(0)->hitNormal.vector).normalized() << std::endl << std::endl;

    //std::cout << "--------------------- (3x3) matrixes ---------------------" << "\n";
    //std::cout <<  "transform: \n"                      << (intersection.getHit(0)->hitObject->getTransform().topLeftCorner<3, 3>() * intersection.getHits(0)->hitNormal.vector.head(3)).normalized() << std::endl << std::endl;
    //std::cout <<  "transform and transpose: \n"        << (intersection.getHits(0)->hitObject->getTransform().topLeftCorner<3, 3>().transpose() * intersection.getHit(0)->hitNormal.vector.head(3)).normalized() << std::endl << std::endl;
    //std::cout <<  "inversetransform: \n"               << (intersection.getHits(0)->hitObject->getInverseTransform().topLeftCorner<3, 3>() * intersection.getHit(0)->hitNormal.vector.head(3)).normalized() << std::endl << std::endl;

    std::cout << "matrix: \n" << (intersection.getHit(0)->hitObject->getInverseTransform().topLeftCorner<3, 3>().transpose()) << std::endl << std::endl;
    std::cout << "normal: \n" << intersection.getHit(0)->hitNormal.vector.head(3) << std::endl << std::endl;
    std::cout << "inversetransform and transpose 1: \n" << (intersection.getHit(0)->hitObject->getInverseTransform().topLeftCorner<3, 3>().transpose() *
                                                            intersection.getHit(0)->hitNormal.vector.head(3)).normalized() << std::endl << std::endl;
    std::cout << "inversetransform and transpose 2: \n" << (intersection.getHit(0)->hitObject->getInverseTransform().topLeftCorner<3, 3>().transpose() *
                                                            intersection.getHit(0)->hitNormal.vector.head(3).normalized()).normalized() << std::endl << std::endl;
    std::cout << "inversetransform and transpose 3: \n" << (intersection.getHit(0)->hitObject->getInverseTransform().topLeftCorner<3, 3>().transpose() *
                                                            intersection.getHit(0)->hitNormal.vector.normalized().head(3)).normalized() << std::endl << std::endl;

    //Eigen::Matrix4d matrix = Eigen::Matrix4d::Identity();
    Eigen::Matrix3d matrix = intersection.getHit(0)->hitObject->getInverseTransform().topLeftCorner<3, 3>().transpose();
    double threshold = 1e-14;
    matrix = matrix.unaryExpr([threshold](double x) {
        return std::abs(x) < threshold ? 0 : x;
    });

    std::cout << matrix;
    std::cout << "inversetransform and transpose 1: \n" << (matrix * intersection.getHit(0)->hitNormal.vector.head(3)).normalized() << std::endl << std::endl;


    REQUIRE(intersection.numHits == 2);
    REQUIRE(intersection.getHit(0)->isEntering);
    REQUIRE(!intersection.getHit(1)->isEntering);

    REQUIRE((sphere->getTransform() * intersection.getHit(0)->hitPoint.point).isApprox(Point3(-1, -1, 0).point, 0.001));
    REQUIRE((sphere->getTransform() * intersection.getHit(1)->hitPoint.point).isApprox(Point3(-0.96, -0.98, 1).point, 0.001));
}