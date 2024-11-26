//
// Created by berka on 10/10/2024.
//

#ifndef RAYTRACINGENGINE_OBJECTFACTORY_H
#define RAYTRACINGENGINE_OBJECTFACTORY_H

#include "memory"
#include "Geometry/include/unitGeometricObjects/HitObject.h"
#include "Math/include/TransformationManager.h"
#include "Rendering/include/Shaders/Material/AbstractMaterial.h"
#include "Geometry/include/unitGeometricObjects/Booleans/Boolean.h"
#include "Geometry/include/unitGeometricObjects/PrimitiveObjects.h"
#include "Geometry/include/unitGeometricObjects/Booleans/UnionBool.h"
#include "Geometry/include/unitGeometricObjects/Booleans/IntersectionBool.h"
#include "Geometry/include/unitGeometricObjects/Booleans/DifferenceBool.h"
#include "Geometry/include/unitGeometricObjects/UnitSphere.h"
#include "Geometry/include/unitGeometricObjects/UnitCube.h"
#include "Rendering/include/Shaders/Material/FresnelMaterial.h"

class ObjectFactory {
public:

    template<class T>
    static std::shared_ptr<PrimitiveObjects> createObject(const std::shared_ptr<AbstractMaterial> &material){
        static_assert(std::is_base_of<PrimitiveObjects, T>::value, "T must inherit from PrimitiveObjects");
        return std::make_shared<T>(material);
    }

    template<class T>
    static std::shared_ptr<PrimitiveObjects> createObject(TransformationManager &manager, std::shared_ptr<AbstractMaterial> &material){
        static_assert(std::is_base_of<PrimitiveObjects, T>::value, "T must inherit from PrimitiveObjects");
        std::shared_ptr<PrimitiveObjects> object = std::make_shared<T>(material);
        object->setTransformations(manager);
        return object;
    }

    template<class T>
    static std::shared_ptr<Boolean> createBoolObject(std::shared_ptr<HitObject> left, std::shared_ptr<HitObject> right){
        static_assert(std::is_base_of<Boolean, T>::value, "T must inherit from HitObject");
        std::shared_ptr<Boolean> object = std::make_shared<T>(left, right);
        return object;
    }

};


#endif //RAYTRACINGENGINE_OBJECTFACTORY_H
