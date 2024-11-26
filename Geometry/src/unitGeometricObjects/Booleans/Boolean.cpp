//
// Created by berka on 24/11/2024.
//

#include "Geometry/include/unitGeometricObjects/Booleans/Boolean.h"
#include "Intersection.h"

bool Boolean::hit(const Ray &incomingRay, Intersection &intersection) {
    Intersection leftInter, rightInter;

    bool test = left->hit(incomingRay, leftInter);
    bool test2 = right->hit(incomingRay, rightInter);

    if(!test && !test2){
        return false;
    }

    intersection = useOperation(leftInter, rightInter);

    return (intersection.numHits > 0);
}
