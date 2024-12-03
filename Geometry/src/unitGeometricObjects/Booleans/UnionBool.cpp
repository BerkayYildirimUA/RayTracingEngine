//
// Created by berka on 24/11/2024.
//

#include "Geometry/include/unitGeometricObjects/Booleans/UnionBool.h"
#include "Intersection.h"
#include "HitInfo.h"

Intersection UnionBool::useOperation(const Intersection &left, const Intersection &right) const {
    Intersection result;

    int leftIndex = 0, rightIndex = 0;


    bool leftInside = (left.numHits > 0) ? !left.getHit(0)->isEntering : false;
    bool rightInside = (right.numHits > 0) ? !right.getHit(0)->isEntering : false;
    bool combInside = leftInside || rightInside;

    while (leftIndex < left.numHits || rightIndex < right.numHits) { //while one still full
        HitInfo *currentHit = nullptr;

        // left not empty and (right empty or (left <= right))
        if (leftIndex < left.numHits &&
            (rightIndex >= right.numHits || (left.getHit(leftIndex)->hitTime <= right.getHit(rightIndex)->hitTime))) {
            currentHit = left.getHit(leftIndex).get();
            leftInside = currentHit->isEntering;
            ++leftIndex;
        } else {
            currentHit = right.getHit(rightIndex).get();
            rightInside = currentHit->isEntering;
            ++rightIndex;
        }

        bool newCombInside = leftInside || rightInside;

        if (newCombInside != combInside) {
            combInside = newCombInside;
            result.resize(result.numHits + 1);
            auto &newHit = result.getHit(result.numHits++);
            newHit = std::make_unique<HitInfo>(*currentHit);
        }
    }

    return result;
}

bool UnionBool::hit(const Ray &incomingRay) const {
    bool leftBool = left->hit(incomingRay);
    bool rightBool = right->hit(incomingRay);


    return leftBool || rightBool;
}
