//
// Created by berka on 26/11/2024.
//
#include "Geometry/include/unitGeometricObjects/PrimitiveObjects.h"
#include "Geometry/include/unitGeometricObjects/HitObject.h"
#include "Core/include/Ray.h"
#include "Geometry/include/Intersection.h"
#include "Math/include/TransformationManager.h"
#include "Rendering/include/Shaders/Material/AbstractMaterial.h"

void PrimitiveObjects::transformRayToObjectSpace(const Ray& incomingRay, Ray &genRay) const {

    genRay.dir.vector = inverseTransform * incomingRay.dir.vector;
    genRay.start.point = inverseTransform * incomingRay.start.point;
}

const Eigen::Matrix4d &PrimitiveObjects::getInverseTransform() const {
    return inverseTransform;
}

const Eigen::Matrix4d &PrimitiveObjects::getTransform() const {
    return transform;
}
