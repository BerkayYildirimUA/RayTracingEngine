//
// Created by berka on 08/10/2024.
//

#include "../include/Intersection.h"
#include "../include/HitInfo.h"

void Intersection::set(Intersection &intersection) {
    this->hits = std::move(intersection.hits);
    this->numHits = intersection.numHits;
}

std::unique_ptr<HitInfo> &Intersection::getHits(int i) {
    auto &info = hits[i];

    if (isNull(i)) {
        info = std::make_unique<HitInfo>();
    }

    return info;
}

bool Intersection::isNull(int i) {
    if (!hits[i]) {
        return true;
    }

    return false;
}
