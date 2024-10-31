//
// Created by berka on 10/10/2024.
//

#include "../../include/unitGeometricObjects/UnitCircle.h"
#include "../../include/HitInfo.h"
#include "memory"
#include "iostream"

bool UnitSphere::hit(const Ray &incomingRay, Intersection &intersection) const {
    Ray genRay;
    this->transformRayToObjectSpace(incomingRay, genRay);

    double A, B, C;

    Eigen::Vector3d direction(genRay.dir.vector.x(), genRay.dir.vector.y(), genRay.dir.vector.z());
    Eigen::Vector3d start(genRay.start.point.x(), genRay.start.point.y(), genRay.start.point.z());


    A = calcNorm(direction, direction);
    assert(A > 0);
    B = calcNorm(start, direction);
    C = calcNorm(start, start) - 1.0;

    bool isInside = false;
    if (C < 0){
        isInside = true;
    }

    double discrim = B * B - A * C; // ax^2 + 2bx + c --> 4b^2 - 4AC

    if (discrim < 0.0) {
        return false;
    }

    int numberOfHits = 0;
    double discRoot = sqrt(discrim);
    double t1 = (-B - discRoot) / A;
    double t2 = (-B + discRoot) / A;


    if (t1 > 0.00001) {
        auto &info = intersection.getHits(0);

        info->hitTime = t1;
        info->hitObject = const_cast<UnitSphere *>(this)->shared_from_this();
        info->isEntering = true;
        info->surface = 0;

        Eigen::Vector3d point = genRay.calcPoint(t1);
        info->hitPoint.set(point.x(), point.y(), point.z());

        if (isInside){
            Vector3 norm(-point.x(), -point.y(), -point.z());
            info->hitNormal.set(norm);
        } else {
            Vector3 norm(point.x(), point.y(), point.z());
            info->hitNormal.set(norm);
        }

        numberOfHits = 1;
    }

    if (t2 > 0.00001 && (std::abs(t1 - t2) > 0.00001)) {
        auto &info = intersection.getHits(numberOfHits);

        info->hitTime = t2;
        info->hitObject = const_cast<UnitSphere *>(this)->shared_from_this();
        info->isEntering = false;
        info->surface = 0;

        Eigen::Vector3d point = genRay.calcPoint(t2);
        info->hitPoint.set(point.x(), point.y(), point.z());

        if (isInside){
            Vector3 norm(-point.x(), -point.y(), -point.z());
            info->hitNormal.set(norm);
        } else {
            Vector3 norm(point.x(), point.y(), point.z());
            info->hitNormal.set(norm);
        }

        numberOfHits++;
    }

    intersection.numHits = numberOfHits;

    return (numberOfHits > 0);

}

UnitSphere::UnitSphere(const std::shared_ptr<AbstractMaterial> &material1) : HitObject(material1) {

}

bool UnitSphere::hit(const Ray &incomingRay) const {
    Ray genRay;
    this->transformRayToObjectSpace(incomingRay, genRay);

    double A, B, C;

    Eigen::Vector3d direction(genRay.dir.vector.x(), genRay.dir.vector.y(), genRay.dir.vector.z());
    Eigen::Vector3d start(genRay.start.point.x(), genRay.start.point.y(), genRay.start.point.z());

    A = calcNorm(direction, direction);
    assert(A > 0);
    B = calcNorm(start, direction);
    C = calcNorm(start, start) - 1.0;

    double discrim = B * B - A * C; // ax^2 + 2bx + c --> 4b^2 - 4AC

    if (discrim < 0.0) {
        return false;
    }

    double discRoot = sqrt(discrim);
    double t1 = (-B - discRoot) / A;

    if (t1 > 0 && t1 < 1){
        return true;
    }

    double t2 = (-B + discRoot) / A;

    if (t2 > 0 && t2 < 1){
        return true;
    }

    return false;
}

