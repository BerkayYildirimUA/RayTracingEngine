//
// Created by berka on 24/11/2024.
//

#ifndef RAYTRACINGENGINE_INTERSECTIONBOOL_H
#define RAYTRACINGENGINE_INTERSECTIONBOOL_H

#include "Boolean.h"
class IntersectionBool : public Boolean{
public:
    explicit IntersectionBool(const std::shared_ptr<HitObject>& leftObj, const std::shared_ptr<HitObject>& rightObj) {
        setLeft(leftObj);
        setRight(rightObj);
    }

    bool hit(const Ray &incomingRay) const override;

private:
    Intersection useOperation(const Intersection &left, const Intersection &right) const override;
};


#endif //RAYTRACINGENGINE_INTERSECTIONBOOL_H
