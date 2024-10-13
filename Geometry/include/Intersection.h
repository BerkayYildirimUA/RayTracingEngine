//
// Created by berka on 08/10/2024.
//

#ifndef RAYTRACINGENGINE_INTERSECTION_H
#define RAYTRACINGENGINE_INTERSECTION_H

#include <vector>
#include <memory>
#include "HitInfo.h"

class Intersection {
public:
    std::vector<std::unique_ptr<HitInfo>> hits;
    int numHits = 0;
};


#endif //RAYTRACINGENGINE_INTERSECTION_H
