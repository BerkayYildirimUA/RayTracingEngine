//
// Created by berka on 10/10/2024.
//

#ifndef RAYTRACINGENGINE_OBJECTFACTORY_H
#define RAYTRACINGENGINE_OBJECTFACTORY_H

#include "memory"
#include "Geometry/include/unitGeometricObjects/HitObject.h"
#include "Math/include/TransformationManager.h"

class ObjectFactory {
public:

    template<class T>
    static std::shared_ptr<HitObject> createObject(){
        static_assert(std::is_base_of<HitObject, T>::value, "T must inherit from HitObject");
        return std::make_shared<T>();
    }

    template<class T>
    static std::shared_ptr<HitObject> createObject(TransformationManager &manager){
        static_assert(std::is_base_of<HitObject, T>::value, "T must inherit from HitObject");

        std::shared_ptr<HitObject> object = std::make_shared<T>();

        object->setTransformations(manager);

        return object;
    }

};


#endif //RAYTRACINGENGINE_OBJECTFACTORY_H
