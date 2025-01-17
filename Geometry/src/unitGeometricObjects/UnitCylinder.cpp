//
// Created by berka on 15/01/2025.
//

#include "Geometry/include/unitGeometricObjects/UnitCylinder.h"
#include "HitInfo.h"
#include "memory"
#include "Intersection.h"

bool UnitCylinder::hit(const Ray &incomingRay, Intersection &intersection) const {
    Ray genRay;
    this->transformRayToObjectSpace(incomingRay, genRay);


    double A, B, C, d, F;

    d = (this->s - 1) * genRay.dir.getZ();
    F = 1 + (this->s - 1) * genRay.start.getZ();

    A = genRay.dir.getX() * genRay.dir.getX() + genRay.dir.getY() * genRay.dir.getY() - d * d;

    B = genRay.start.getX() * genRay.dir.getX() + genRay.start.getY() * genRay.dir.getY() - F * d;

    C = genRay.start.getX() * genRay.start.getX() + genRay.start.getY() * genRay.start.getY() - F * F;

    double discrim = B * B - A * C; // ax^2 + 2bx + c --> 4b^2 - 4AC

    if (discrim < 0.0) {
        return false;
    }

    int numberOfHits = 0;
    double discRoot = sqrt(discrim);

    double t1 = (-B - discRoot) / A;
    double t2 = (-B + discRoot) / A;

    Eigen::Vector3d pointT1 = genRay.calcPoint(t1);
    Eigen::Vector3d pointT2 = genRay.calcPoint(t2);


    double tCap = (1 - genRay.start.getZ()) / genRay.dir.getZ();
    Eigen::Vector3d pointCap = genRay.calcPoint(tCap);

    double tBase = (0 - genRay.start.getZ()) / genRay.dir.getZ();
    Eigen::Vector3d pointBase = genRay.calcPoint(tBase);

    if (A == 0){
        if (tBase >= tCap && tBase > 0){
            t1 = tBase;
            pointT1 = pointBase;
            t2 = tCap;
            pointT2 = pointCap;
        } else if (tBase < tCap && tCap > 0){
            t1 = tCap;
            pointT1 = pointCap;

            t2 = tBase;
            pointT2 = pointBase;
        }
    }

    if ((A != 0 && pointBase.x() * pointBase.x() + pointBase.y() * pointBase.y() <= 1)){
        if (tBase > 0) {
            if (pointT1.z() < 0) {
                t1 = tBase;
                pointT1 = pointBase;
            } else if (pointT2.z() < 0) {
                t2 = tBase;
                pointT2 = pointBase;
            }
        }
    }

    if ((A != 0 && pointCap.x() * pointCap.x() + pointCap.y() * pointCap.y() <= s * s)){
        if (tCap > 0) {
            if (pointT1.z() > 1){
                t1 = tCap;
                pointT1 = pointCap;
            } else if (pointT2.z() > 1){
                t2 = tCap;
                pointT2 = pointCap;
            }
        }
    }

    if (t2 > 0 && t1 > t2) {
        std::swap(t1, t2);
        std::swap(pointT1, pointT2);
    }

    // DONT CHANGE ANTYTHING BELOW HERE

    if (t1 > 0.00001 && pointT1.z() >= 0 && pointT1.z() <= 1) {

        bool isBase = std::abs(pointT1.z()) < 1e-6 && (pointT1.x() * pointT1.x() + pointT1.y() * pointT1.y() < 1);
        bool isCap = std::abs(pointT1.z() - 1) < 1e-6 && (pointT1.x() * pointT1.x() + pointT1.y() * pointT1.y() < s * s);

        auto &info = intersection.getHit(0);

        info->hitTime = t1;

        if (isBase){
            info->surface = 1;
        } else if (isCap) {
            info->surface = 2;
        } else {
            info->surface = 0; // wall
        }

        info->isEntering = true;
        info->hitObject = std::static_pointer_cast<PrimitiveObjects>(
                const_cast<UnitCylinder*>(this)->shared_from_this()
        );

        info->hitPoint.set(pointT1.x(), pointT1.y(), pointT1.z());

        Vector3 norm;

        if (isBase){
            norm.set(0, 0, 1);
        } else if (isCap) {
            norm.set(0, 0, -1);
        } else {
            norm.set(pointT1.x(), pointT1.y(), -(this->s - 1) * (1 + (this->s - 1) * pointT1.z()));
        }

        info->hitNormal.set(norm);


        numberOfHits = 1;

    }

    if (t2 > 0.00001 && (std::abs(t1 - t2) > 0.00001) && pointT2.z() >= 0 && pointT2.z() <= 1){

        bool isBase = std::abs(pointT2.z()) < 1e-6 && (pointT2.x() * pointT2.x() + pointT2.y() * pointT2.y() < 1);
        bool isCap = std::abs(pointT2.z() - 1) < 1e-6 && (pointT2.x() * pointT2.x() + pointT2.y() * pointT2.y() < s * s);

        auto &info = intersection.getHit(numberOfHits);

        info->hitTime = t2;

        if (isBase){
            info->surface = 1;
        } else if (isCap) {
            info->surface = 2;
        } else {
            info->surface = 0; // wall
        }

        info->isEntering = false;
        info->hitObject = std::static_pointer_cast<PrimitiveObjects>(
                const_cast<UnitCylinder*>(this)->shared_from_this()
        );

        info->hitPoint.set(pointT2.x(), pointT2.y(), pointT2.z());

        Vector3 norm;

        if (isBase){
            norm.set(0, 0, 1);
        } else if (isCap) {
            norm.set(0, 0, -1);
        } else {
            norm.set(pointT2.x(), pointT2.y(), -(this->s - 1) * (1 + (this->s - 1) * pointT2.z()));
        }

        if (genRay.dir * norm > 0 && t1 < 0){ // dot product
            norm = -norm;
        }

        info->hitNormal.set(norm);

        numberOfHits++;
    }


    intersection.numHits = numberOfHits;
    return (numberOfHits > 0);
}

bool UnitCylinder::hit(const Ray &incomingRay) const {
    Ray genRay;
    this->transformRayToObjectSpace(incomingRay, genRay);


    double A, B, C, d, F;

    d = (this->s - 1) * genRay.dir.getZ();
    F = 1 + (this->s - 1) * genRay.start.getZ();

    A = genRay.dir.getX() * genRay.dir.getX() + genRay.dir.getY() * genRay.dir.getY() - d * d;

    B = genRay.start.getX() * genRay.dir.getX() + genRay.start.getY() * genRay.dir.getY() - F * d;

    C = genRay.start.getX() * genRay.start.getX() + genRay.start.getY() * genRay.start.getY() - F * F;

    double discrim = B * B - A * C; // ax^2 + 2bx + c --> 4b^2 - 4AC

    if (discrim < 0.0) {
        return false;
    }

    double discRoot = sqrt(discrim);

    double t1 = (-B - discRoot) / A;
    double t2 = (-B + discRoot) / A;

    Eigen::Vector3d pointT1 = genRay.calcPoint(t1);
    Eigen::Vector3d pointT2 = genRay.calcPoint(t2);


    double tCap = (1 - genRay.start.getZ()) / genRay.dir.getZ();
    Eigen::Vector3d pointCap = genRay.calcPoint(tCap);

    double tBase = (0 - genRay.start.getZ()) / genRay.dir.getZ();
    Eigen::Vector3d pointBase = genRay.calcPoint(tBase);

    if (A == 0){
        if (tBase > 0 || tCap > 0){
            return true;
        }
    }

    if ((pointBase.x() * pointBase.x() + pointBase.y() * pointBase.y() <= 1)){
        if (tBase > 0) {
            if (pointT1.z() < 0 || pointT2.z() < 0) {
                return true;
            }
        }
    }

    if ((pointCap.x() * pointCap.x() + pointCap.y() * pointCap.y() <= s * s)){
        if (tCap > 0) {
            if (pointT1.z() > 1 || pointT2.z() > 1){
                return true;
            }
        }
    }

    Eigen::Vector3d point = genRay.calcPoint(t1);
    if (t1 > 0 && t1 < 1 &&  point.z() >= 0 && point.z() <= 1){
        return true;
    }
    point = genRay.calcPoint(t2);
    if (t2 > 0 && t2 < 1 && point.z() >= 0 && point.z() <= 1){
        return true;
    }

    return false;
}

UnitCylinder::UnitCylinder(const std::shared_ptr<AbstractMaterial> &material, double s) : PrimitiveObjects(material) { this->s = s;}