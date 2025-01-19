//
// Created by berka on 24/11/2024.
//

#include "Geometry/include/unitGeometricObjects/Booleans/DifferenceBool.h"
#include "Intersection.h"

Intersection DifferenceBool::useOperation(const Intersection &left, const Intersection &right) const {
    Intersection result;

    int leftIndex = 0, rightIndex = 0;


    bool leftInside = (left.numHits > 0) ? !left.getHit(0)->isEntering : false;
    bool rightInside = (right.numHits > 0) ? !right.getHit(0)->isEntering : false;
    bool combInside = leftInside && !rightInside;


    while (leftIndex < left.numHits) { //while left not empty
        HitInfo* currentHit = nullptr;

        if (leftIndex < left.numHits && (rightIndex >= right.numHits || left.getHit(leftIndex)->hitTime <= right.getHit(rightIndex)->hitTime)) {
            currentHit = left.getHit(leftIndex).get();
            leftInside = currentHit->isEntering;
            ++leftIndex;
        } else {
            currentHit = right.getHit(rightIndex).get();
            rightInside = currentHit->isEntering;

            currentHit->hitNormal = -currentHit->hitNormal;
            ++rightIndex;
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

bool DifferenceBool::hit(const Ray &incomingRay) const {
    Intersection leftInt, rightInt;

    this->left->hit(incomingRay, leftInt);
    this->right->hit(incomingRay, rightInt);

    int leftIndex = 0;
    int rightIndex = 0;

    bool insideLeft = (leftInt.numHits > 0) ? !rightInt.getHit(0)->isEntering : false;
    bool insideRight = (leftInt.numHits > 0) ? !rightInt.getHit(0)->isEntering : false;
    bool combInside = insideLeft && !insideRight;

    double maxHitTime = 0;

    while (leftIndex < leftInt.numHits || rightIndex < rightInt.numHits) {
        HitInfo* nextEvent;
        char side;
        bool isEntering;

        if (leftIndex < leftInt.numHits && (rightIndex >= rightInt.numHits || leftInt.getHit(leftIndex)->hitTime <= rightInt.getHit(rightIndex)->hitTime)) {
            nextEvent = leftInt.getHit(leftIndex).get();
            side = 'L';
            isEntering = nextEvent->isEntering;
            maxHitTime = leftInt.getHit(leftIndex)->hitTime;
            leftIndex++;
        } else {
            nextEvent = rightInt.getHit(rightIndex).get();
            side = 'R';
            isEntering = nextEvent->isEntering;
            maxHitTime = rightInt.getHit(rightIndex)->hitTime;
            rightIndex++;
        }

        if (maxHitTime > 1){
            return false;
        }

        if (side == 'L') {
            insideLeft = isEntering;
        } else {
            insideRight = isEntering;
        }

        bool newCombInside = insideLeft && !insideRight;

        if (newCombInside != combInside) {
            return true;
        }
    }

    return false;
}

