//
// Created by berka on 10/10/2024.
//

#include "../../include/unitGeometricObjects/UnitCircle.h"
#include "../../include/HitInfo.h"
#include "memory"

UnitCircle::UnitCircle() {

}

bool UnitCircle::hit(const Ray &incomingRay, Intersection &intersection){
    transformRayToObjectSpace(incomingRay);
    double A, B, C;

    Eigen::Vector3d direction(incomingRay.dir.vector.x(), incomingRay.dir.vector.y(), incomingRay.dir.vector.z());
    Eigen::Vector3d start(incomingRay.start.point.x(), incomingRay.start.point.y(), incomingRay.start.point.z());


    A = calcNorm(direction, direction);
    B = calcNorm(start, direction);
    C = calcNorm(start, start) - 1.0;

    double discrim = B*B - A*C; // ax^2 + 2bx + c --> 4b^2 - 4AC

    if (discrim < 0.0){
        return false;
    }

    int numberOfHits = 0;
    double discRoot = sqrt(discrim);
    double t1 = (-B - discRoot)/A;

    if (t1 > 0.00001){
        auto &info = intersection.getHits(0);

        info->hitTime = t1;
        info->hitObject = const_cast<UnitCircle*>(this)->shared_from_this();
        info->isEntering = true;
        info->surface = 0;
        Eigen::Matrix<double, 3, 1> point = genRay.calcPoint(t1);
        info->hitPoint.set(point.x(), point.y(), point.z());
        info->hitNormal.set(point.x(), point.y(), point.z());
        numberOfHits = 1;
    }

    double t2 = (-B + discRoot)/A;
    if (t2 > 0.00001 && (std::abs(t1 - t2) > 0.00001)){
        auto &info = intersection.getHits(numberOfHits);

        info->hitTime = t2;
        info->hitObject = const_cast<UnitCircle*>(this)->shared_from_this();
        info->isEntering = false;
        info->surface = 0;
        Eigen::Matrix<double, 3, 1> point = genRay.calcPoint(t2);
        info->hitPoint.set(point.x(), point.y(), point.z());
        info->hitNormal.set(point.x(), point.y(), point.z());
        numberOfHits++;
    }

    intersection.numHits = numberOfHits;

    return (numberOfHits > 0);

}

