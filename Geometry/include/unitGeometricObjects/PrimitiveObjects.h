//
// Created by berka on 26/11/2024.
//

#ifndef RAYTRACINGENGINE_PRIMITIVEOBJECTS_H
#define RAYTRACINGENGINE_PRIMITIVEOBJECTS_H
#include <memory>
#include <Eigen/Core>
#include "HitObject.h"
#include "TransformationManager.h"
#include "Rendering/include/Shaders/Material/AbstractMaterial.h"

class Intersection;

class PrimitiveObjects : public HitObject {
protected:
    Eigen::Matrix4d inverseTransform = Eigen::Matrix4d::Identity();
    Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();

public:
    std::shared_ptr<AbstractMaterial> material;

    const Eigen::Matrix4d &getInverseTransform() const;

    const std::shared_ptr<AbstractMaterial> &getMaterial() const {
        return material;
    }

    void setMaterial(const std::shared_ptr<AbstractMaterial> &material) {
        PrimitiveObjects::material = material;
    }

    const Eigen::Matrix4d &getTransform() const;

    virtual void setTransformations(TransformationManager &manager){
        std::pair<Eigen::Matrix4d, Eigen::Matrix4d> pair = manager.getTotalTransformation();

        transform = pair.first;
        inverseTransform = pair.second;
    }

    void transformRayToObjectSpace (const Ray& incomingRay, Ray &genRay) const;

    explicit PrimitiveObjects(const std::shared_ptr<AbstractMaterial> &material) : material(material) {};

};

#endif //RAYTRACINGENGINE_PRIMITIVEOBJECTS_H
