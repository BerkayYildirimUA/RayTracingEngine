//
// Created by berka on 10/10/2024.
//

#ifndef RAYTRACINGENGINE_HITOBJECT_H
#define RAYTRACINGENGINE_HITOBJECT_H

#include <memory>
#include "Ray.h"

class Intersection;

class HitObject : public std::enable_shared_from_this<HitObject> {
public:

    virtual bool hit(const Ray &incomingRay, Intersection &intersection) const = 0;
    virtual bool hit(const Ray &incomingRay) const = 0;

};


#endif //RAYTRACINGENGINE_HITOBJECT_H
