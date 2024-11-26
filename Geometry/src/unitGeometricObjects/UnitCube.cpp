//
// Created by berka on 15/10/2024.
//

#include "Geometry/include/unitGeometricObjects/UnitCube.h"

bool UnitCube::hit(const Ray &incomingRay, Intersection &intersection)  {
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
    if (tIn > 0.00001 ){
        auto& info = intersection.getHit(num);

        info->hitTime = tIn;
        info->surface = inSurf;
        info->isEntering = true;
        info->hitObject = shared_from_this();

        Eigen::Matrix<double, 3, 1> point = genRay.calcPoint(tIn);
        info->hitPoint.set(point.x(), point.y(), point.z());

        Eigen::Vector3d cubeNorm = cubeNormal(inSurf);

        if (genRay.dir.vector.head(3).dot(cubeNorm) > 0){
            cubeNorm = -cubeNorm;
        }

        /*if(this->isInsideCube(genRay.start)){
            cubeNorm = -cubeNorm;
        }*/

        info->hitNormal.set(cubeNorm.x(), cubeNorm.y(), cubeNorm.z());
        num++;
    }

    if (tOut > 0.00001){
        auto& info = intersection.getHit(num);

        info->hitTime = tOut;
        info->surface = outSurf;
        info->isEntering = false;
        info->hitObject = shared_from_this();

        Eigen::Matrix<double, 3, 1> point = genRay.calcPoint(tOut);
        info->hitPoint.set(point.x(), point.y(), point.z());

        Eigen::Vector3d cubeNorm = cubeNormal(outSurf);

        if (genRay.dir.vector.head(3).dot(cubeNorm) > 0){
            cubeNorm = -cubeNorm;
        }

        /*if(this->isInsideCube(genRay.start)){
            cubeNorm = -cubeNorm;
        }*/

        info->hitNormal.set(cubeNorm.x(), cubeNorm.y(), cubeNorm.z());

        num++;
    }

    intersection.numHits = num;
    return (num > 0);
}

Eigen::Vector3d UnitCube::cubeNormal(int side) const {

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

bool UnitCube::hit(const Ray &incomingRay) const {
    Ray genRay;
    this->transformRayToObjectSpace(incomingRay, genRay);


    double tHit, numer, denom;
    double tIn = -1000000.0, tOut = 1000000.0;

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
                }
            } else {
                if(tHit > tIn){
                    tIn = tHit;
                }
            }
        }

        if (tIn >= tOut){
            return false;
        }
    }

    if (tIn > 0 && tIn < 1){
        return true;
    }
    if (tOut > 0 && tOut < 1){
        return true;
    }

    return false;
}
