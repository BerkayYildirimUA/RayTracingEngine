//
// Created by berka on 24/11/2024.
//

#ifndef RAYTRACINGENGINE_DIFFERENCEBOOL_H
#define RAYTRACINGENGINE_DIFFERENCEBOOL_H

#include "Boolean.h"
class DifferenceBool : Boolean{

    Intersection useOperation(const Intersection &left, const Intersection &right) const override {
        return Intersection();
    }
};


#endif //RAYTRACINGENGINE_DIFFERENCEBOOL_H
