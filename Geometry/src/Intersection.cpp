//
// Created by berka on 08/10/2024.
//

#include "../include/Intersection.h"
#include "../include/HitInfo.h"

void Intersection::set(Intersection &intersection) {
    this->hits = std::move(intersection.hits);
    this->numHits = intersection.numHits;
}
