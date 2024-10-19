//
// Created by berka on 19/10/2024.
//

#ifndef RAYTRACINGENGINE_BLACKHOLE_H
#define RAYTRACINGENGINE_BLACKHOLE_H

#include "unitGeometricObjects/HitObject.h"
#include "unitGeometricObjects/UnitCircle.h"
#include "Math/include/TransformationManager.h"
#include "unitGeometricObjects/ObjectFactory.h"


[[deprecated("This class is deprecated. Use NewClass instead.")]];
class BlackHole : public HitObject {

    std::shared_ptr<HitObject> core = ObjectFactory::createObject<UnitCircle>();
    std::shared_ptr<HitObject> sphereOfInfluence = ObjectFactory::createObject<UnitCircle>();

    int blackholeMass = 10000;



public:
    BlackHole();

    bool hit(const Ray &incomingRay, Intersection &intersection) override;

    void setTransformations(TransformationManager &manager) override {
        TransformationManager managerCopy = manager;

        core->setTransformations(manager);

        managerCopy.pushScale(10, 10, 10);
        sphereOfInfluence->setTransformations(managerCopy);

    }
};


#endif //RAYTRACINGENGINE_BLACKHOLE_H
