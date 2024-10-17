//
// Created by berka on 15/10/2024.
//

#ifndef RAYTRACINGENGINE_UNITCUBE_H
#define RAYTRACINGENGINE_UNITCUBE_H

#include "HitObject.h"

class UnitCube : public HitObject {
public:
    bool hit(const Ray &incomingRay, Intersection &intersection) override;

};


#endif //RAYTRACINGENGINE_UNITCUBE_H
