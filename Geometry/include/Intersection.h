//
// Created by berka on 08/10/2024.
//

#ifndef RAYTRACINGENGINE_INTERSECTION_H
#define RAYTRACINGENGINE_INTERSECTION_H

#include <vector>
#include <memory>
#include "HitInfo.h"

class Intersection {
private:
    std::array<std::unique_ptr<HitInfo>, 8> hits;
public:
    int numHits = 0;

    void set(Intersection& intersection);

    std::unique_ptr<HitInfo> &getHits(int i);

    bool isNull(int i);
};


#endif //RAYTRACINGENGINE_INTERSECTION_H
