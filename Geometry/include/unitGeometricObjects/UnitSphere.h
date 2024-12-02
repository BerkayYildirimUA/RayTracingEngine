//
// Created by berka on 10/10/2024.
//

#ifndef RAYTRACINGENGINE_UNITSPHERE_H
#define RAYTRACINGENGINE_UNITSPHERE_H

#include "HitObject.h"
#include "Core/include/Ray.h"
#include "../Intersection.h"
#include "PrimitiveObjects.h"


class UnitSphere : public PrimitiveObjects {
public:
    bool hit(const Ray &incomingRay, Intersection &intersection) const override;
    bool hit(const Ray &incomingRay) const override;

    explicit UnitSphere(const std::shared_ptr<AbstractMaterial> &material);
};


#endif //RAYTRACINGENGINE_UNITSPHERE_H
