//
// Created by berka on 24/11/2024.
//

#include "Geometry/include/unitGeometricObjects/Booleans/DifferenceBool.h"
#include "Intersection.h"

Intersection DifferenceBool::useOperation(const Intersection &left, const Intersection &right) const { //TODO something wrong here, I can see through door
    Intersection result;

    int leftIndex = 0, rightIndex = 0;


    bool leftInside = false;
    bool rightInside = false;
    bool combInside = false;


    while (leftIndex < left.numHits) { //while both not empty
        HitInfo* currentHit = nullptr;

        if ((rightIndex >= right.numHits) || (left.getHit(leftIndex)->hitTime < right.getHit(rightIndex)->hitTime)) {
            currentHit = left.getHit(leftIndex).get();
            leftInside = currentHit->isEntering;
            ++leftIndex;
        } else {
            currentHit = right.getHit(rightIndex).get();
            rightInside = currentHit->isEntering;
            ++rightIndex;

            //currentHit->hitNormal = -currentHit->hitNormal;

        }


        bool newCombInside = leftInside && !rightInside;

        if (newCombInside != combInside) {
            combInside = newCombInside;
            result.resize(result.numHits + 1);
            auto& newHit = result.getHit(result.numHits++);
            newHit = std::make_unique<HitInfo>(*currentHit);
        }
    }

    return result;
}
