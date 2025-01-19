//
// Created by berka on 24/11/2024.
//

#ifndef RAYTRACINGENGINE_UNIONBOOL_H
#define RAYTRACINGENGINE_UNIONBOOL_H

#include "Boolean.h"

class UnionBool : public Boolean {
public:
    explicit UnionBool(const std::shared_ptr<HitObject>& leftObj, const std::shared_ptr<HitObject>& rightObj) {
        setLeft(leftObj);
        setRight(rightObj);
    }

    Intersection useOperation(const Intersection &left, const Intersection &right) const override;

    bool hit(const Ray &incomingRay) const override;
};


#endif //RAYTRACINGENGINE_UNIONBOOL_H
