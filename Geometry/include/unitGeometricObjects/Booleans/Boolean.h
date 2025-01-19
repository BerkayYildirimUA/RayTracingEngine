//
// Created by berka on 24/11/2024.
//

#ifndef RAYTRACINGENGINE_BOOLEAN_H
#define RAYTRACINGENGINE_BOOLEAN_H

#include "unitGeometricObjects/HitObject.h"

class Boolean: public HitObject {
protected:
    std::shared_ptr<HitObject> left, right;

public:

    virtual Intersection useOperation(const Intersection& left, const Intersection& right) const = 0;

    const std::shared_ptr<HitObject> &getLeft() const {
        return left;
    }

    void setLeft(const std::shared_ptr<HitObject> &left) {
        Boolean::left = left;
    }

    const std::shared_ptr <HitObject>&getRight() const {
        return right;
    }

    void setRight(const std::shared_ptr<HitObject> &right) {
        Boolean::right = right;
    }

    bool hit(const Ray &incomingRay, Intersection &intersection) const override;

};


#endif //RAYTRACINGENGINE_BOOLEAN_H
