//
// Created by berka on 15/10/2024.
//

#include "Geometry/include/unitGeometricObjects/UnitCube.h"

bool UnitCube::hit(const Ray &incomingRay, Intersection &intersection) {
    Ray genRay;
    transformRayToObjectSpace(incomingRay, genRay);
    double tHit, numer, denom;
    double tIn = -1000000.0, tOut = 1000000.0;
    int inSurf, outSurf;

    for (int i = 0; i < 6; i++) {
        switch (i) {
            case 0:
                numer = 1.0 - genRay.start.point.y();
                denom = genRay.dir.vector.y();
                break;

            case 1:
                numer = 1.0 + genRay.start.point.y();
                denom = -genRay.dir.vector.y();
                break;

            case 2:
                numer = 1.0 - genRay.start.point.x();
                denom = genRay.dir.vector.x();
                break;

            case 3:
                numer = 1.0 + genRay.start.point.x();
                denom = -genRay.dir.vector.x();
                break;

            case 4:
                numer = 1.0 - genRay.start.point.z();
                denom = genRay.dir.vector.z();
                break;

            case 5:
                numer = 1.0 + genRay.start.point.z();
                denom = -genRay.dir.vector.z();
                break;

        }

        if (fabs(denom) < 0.00001){
            if(numer < 0){
                return false;
            }
        } else {
            tHit = numer / denom;
            if (denom > 0){
                if(tHit < tOut){
                    tOut = tHit;
                    outSurf = i;
                }
            } else {
                if(tHit > tIn){
                    tIn = tHit;
                    inSurf = i;
                }
            }
        }

        if (tIn >= tOut){
            return false;
        }
    }

    int num = 0;
    if (tIn > 0.00001){
        auto &info = intersection.getHits(0);

        info->hitTime = tIn;
        info->surface = inSurf;
        info->isEntering = true;
        info->hitObject = const_cast<UnitCube*>(this)->shared_from_this();
        Eigen::Matrix<double, 3, 1> point = incomingRay.calcPoint(tIn);
        info->hitPoint.set(point.x(), point.y(), point.z());

        Vector3 cubeNorm = cubeNormal(inSurf);
        cubeNorm.vector = inverseTransform * cubeNorm.vector;
        info->hitNormal.set(cubeNorm);
        num++;
    }

    if (tOut > 0.00001){
        auto &info = intersection.getHits(num);

        info->hitTime = tOut;
        info->surface = outSurf;
        info->isEntering = false;
        info->hitObject = const_cast<UnitCube*>(this)->shared_from_this();

        Eigen::Matrix<double, 3, 1> point = incomingRay.calcPoint(tOut);
        info->hitPoint.set(point.x(), point.y(), point.z());

        Vector3 cubeNorm = cubeNormal(inSurf);
        cubeNorm.vector = inverseTransform * cubeNorm.vector;
        info->hitNormal.set(cubeNorm);
        num++;
    }

    intersection.numHits = num;
    return (num > 0);
}

Vector3 UnitCube::cubeNormal(int side) {

    switch (side) {
        case 0:
            return {0, 1, 0};
        case 1:
            return {0, -1, 0};
        case 2:
            return {1, 0, 0};
        case 3:
            return {-1, 0, 0};
        case 4:
            return {0, 0, 1};
        case 5:
            return {0, 0, -1};
    }
    return {-1000, -1000, -1000};
}

UnitCube::UnitCube(const std::shared_ptr<AbstractMaterial> &material1) : HitObject(material1) {

}
