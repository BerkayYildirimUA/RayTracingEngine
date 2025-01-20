//
// Created by berka on 10/10/2024.
//

#include "../../include/unitGeometricObjects/UnitSphere.h"
#include "../../include/HitInfo.h"
#include "memory"
#include "iostream"
#include "Intersection.h"
#include "HitInfo.h"

bool UnitSphere::hit(const Ray &incomingRay, Intersection &intersection) const {
    Ray genRay;
    this->transformRayToObjectSpace(incomingRay, genRay);

    double A, B, C;

    Vector3 direction(genRay.dir.vector.x(), genRay.dir.vector.y(), genRay.dir.vector.z());
    Vector3 start(genRay.start.point.x(), genRay.start.point.y(), genRay.start.point.z());


    A = direction * direction;
    assert(A > 0);
    B = start * direction;
    C = start * start - 1.0;

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
        auto &info = intersection.getHit(0);

        info->hitTime = t1;
        info->surface = 0;
        info->isEntering = true;
        info->hitObject = std::static_pointer_cast<PrimitiveObjects>(
                const_cast<UnitSphere*>(this)->shared_from_this()
        );

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
        auto &info = intersection.getHit(numberOfHits);

        info->hitTime = t2;
        info->surface = 0;
        info->isEntering = false;
        info->hitObject = std::static_pointer_cast<PrimitiveObjects>(
                const_cast<UnitSphere*>(this)->shared_from_this()
        );

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

bool UnitSphere::hit(const Ray &incomingRay) const {
    Ray genRay;
    this->transformRayToObjectSpace(incomingRay, genRay);

    double A, B, C;

    Vector3 direction(genRay.dir.vector.x(), genRay.dir.vector.y(), genRay.dir.vector.z());
    Vector3 start(genRay.start.point.x(), genRay.start.point.y(), genRay.start.point.z());

    A = direction * direction;
    assert(A > 0);
    B = start * direction;
    C = start * start - 1.0;

    if (C > 0){
        return false;
    }


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

UnitSphere::UnitSphere(const std::shared_ptr<AbstractMaterial> &material) : PrimitiveObjects(material) {}

Point3 UnitSphere::getCenter() {
    return {0, 0, 0};
}

