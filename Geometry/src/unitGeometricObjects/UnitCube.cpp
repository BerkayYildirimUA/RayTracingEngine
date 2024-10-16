//
// Created by berka on 15/10/2024.
//

#include "Geometry/include/unitGeometricObjects/UnitCube.h"

bool UnitCube::hit(const Ray &incomingRay, Intersection &intersection) const {

    Ray genRay = transformRayToObjectSpace(incomingRay);
    double tHIt, numer, denom;
    double tIn = -1000000.0, tOut = 1000000.0;
    int inSurf, outSurf;

    return false;
}
