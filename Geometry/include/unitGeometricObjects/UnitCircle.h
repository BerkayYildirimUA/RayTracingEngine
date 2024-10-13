//
// Created by berka on 10/10/2024.
//

#ifndef RAYTRACINGENGINE_UNITCIRCLE_H
#define RAYTRACINGENGINE_UNITCIRCLE_H

#include "HitObject.h"
#include "Core/include/Ray.h"
#include "../Intersection.h"

class UnitCircle : public HitObject {
public:
    UnitCircle();
    bool hit(const Ray &incomingRay, Intersection &intersection) const override;

};


#endif //RAYTRACINGENGINE_UNITCIRCLE_H
