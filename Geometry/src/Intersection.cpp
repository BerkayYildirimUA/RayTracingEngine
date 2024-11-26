//
// Created by berka on 08/10/2024.
//

#include "../include/Intersection.h"
#include "../include/HitInfo.h"

void Intersection::set(Intersection &intersection) {
    this->hits = std::move(intersection.hits);
    this->numHits = intersection.numHits;

    intersection.hits.reserve(2);
    intersection.hits.resize(2);
    intersection.numHits = 0;
}

std::unique_ptr<HitInfo> &Intersection::getHit(int i) {
    if (i >= hits.size()) {
        //std::cout << "rezize from " << hits.size() << "with i: " << i << std::endl;
        hits.resize(i + 1); // Expand vector if out of bounds
    }

    auto& info = hits[i];
    if (!info) {
        info = std::make_unique<HitInfo>();
    }
    return info;
}

Intersection::Intersection(int numHits) : numHits(numHits) {
    hits.reserve(numHits);
    hits.resize(numHits);
}

Intersection::Intersection() {

    //std::cout << "Default constructor called, hits resized to 8.\n";

    hits.reserve(2);
    hits.resize(2);
}


