//
// Created by berka on 08/10/2024.
//

#ifndef RAYTRACINGENGINE_HITINFO_H
#define RAYTRACINGENGINE_HITINFO_H


#include "memory"
#include "Math/include/Point3.h"
#include "Math/include/Vector3.h"
#include "Eigen/Core"

class PrimitiveObjects;

class HitInfo {
public:
    double hitTime;
    std::shared_ptr<PrimitiveObjects> hitObject;

    bool isEntering;
    int surface;
    Point3 hitPoint;
    Vector3 hitNormal;

    HitInfo() = default;

    HitInfo(const HitInfo &other) : hitTime(other.hitTime), hitObject(other.hitObject), isEntering(other.isEntering),
                                    surface(other.surface), hitPoint(other.hitPoint), hitNormal(other.hitNormal) {}

    explicit HitInfo(double hitTime) : hitTime(hitTime) {}

    bool operator<(const HitInfo &other) const {
        return hitTime < other.hitTime;
    }

    bool operator==(const HitInfo &other) const {
        return hitTime == other.hitTime;
    }

};


#endif //RAYTRACINGENGINE_HITINFO_H
