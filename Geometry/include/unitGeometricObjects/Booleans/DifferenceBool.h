//
// Created by berka on 24/11/2024.
//

#ifndef RAYTRACINGENGINE_DIFFERENCEBOOL_H
#define RAYTRACINGENGINE_DIFFERENCEBOOL_H

#include "Boolean.h"
class DifferenceBool : public Boolean{
public:
    explicit DifferenceBool(const std::shared_ptr<HitObject>& leftObj, const std::shared_ptr<HitObject>& rightObj) {
        setLeft(leftObj);
        setRight(rightObj);
    }

    bool hit(const Ray &incomingRay) const override;


private:
    Intersection useOperation(const Intersection &left, const Intersection &right) const override;
};


#endif //RAYTRACINGENGINE_DIFFERENCEBOOL_H
