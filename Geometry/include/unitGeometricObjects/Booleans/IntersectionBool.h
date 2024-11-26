//
// Created by berka on 24/11/2024.
//

#ifndef RAYTRACINGENGINE_INTERSECTIONBOOL_H
#define RAYTRACINGENGINE_INTERSECTIONBOOL_H

#include "Boolean.h"
class IntersectionBool : Boolean{

    Intersection useOperation(const Intersection &left, const Intersection &right) const override {
        return Intersection();
    }
};


#endif //RAYTRACINGENGINE_INTERSECTIONBOOL_H
