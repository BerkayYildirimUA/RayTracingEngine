//
// Created by berka on 10/10/2024.
//

#ifndef RAYTRACINGENGINE_UNITCIRCLE_H
#define RAYTRACINGENGINE_UNITCIRCLE_H

#include "HitObject.h"
#include "Core/include/Ray.h"
#include "../Intersection.h"



class UnitSphere : public HitObject {
public:

    explicit UnitSphere(const std::shared_ptr<AbstractMaterial> &material1);


    bool hit(const Ray &incomingRay, Intersection &intersection) override;
    bool hit(const Ray &incomingRay) const override;

};


#endif //RAYTRACINGENGINE_UNITCIRCLE_H
