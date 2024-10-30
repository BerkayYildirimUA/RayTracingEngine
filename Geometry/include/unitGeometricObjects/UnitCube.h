//
// Created by berka on 15/10/2024.
//

#ifndef RAYTRACINGENGINE_UNITCUBE_H
#define RAYTRACINGENGINE_UNITCUBE_H

#include "HitObject.h"

class UnitCube : public HitObject {
public:
    explicit UnitCube(const std::shared_ptr<AbstractMaterial> &material1);

    bool hit(const Ray &incomingRay, Intersection &intersection) override;

private:

    Eigen::Vector3d cubeNormal(int side);

};


#endif //RAYTRACINGENGINE_UNITCUBE_H
