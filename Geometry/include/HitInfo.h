//
// Created by berka on 08/10/2024.
//

#ifndef RAYTRACINGENGINE_HITINFO_H
#define RAYTRACINGENGINE_HITINFO_H


#include "memory"
#include "Math/include/Point3.h"
#include "Math/include/Vector3.h"
#include "Eigen/Core"

class HitObject;
class HitInfo {
public:
    double hitTime;
    std::shared_ptr<HitObject> hitObject;


    bool isEntering;
    int surface;
    Point3 hitPoint;
    Vector3 hitNormal;

    HitInfo();
};


#endif //RAYTRACINGENGINE_HITINFO_H
