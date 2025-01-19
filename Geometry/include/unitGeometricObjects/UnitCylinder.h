//
// Created by berka on 15/01/2025.
//

#ifndef RAYTRACINGENGINE_UNITCYLINDER_H
#define RAYTRACINGENGINE_UNITCYLINDER_H

#include "PrimitiveObjects.h"

class UnitCylinder : public PrimitiveObjects {


private:
    double s;

public:
    bool hit(const Ray &incomingRay, Intersection &intersection) const override;

    bool hit(const Ray &incomingRay) const override;

    explicit UnitCylinder(const std::shared_ptr<AbstractMaterial> &material, double s);
};


#endif //RAYTRACINGENGINE_UNITCYLINDER_H
