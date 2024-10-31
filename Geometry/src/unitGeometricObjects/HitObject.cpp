//
// Created by berka on 10/10/2024.
//

#include "Geometry/include/unitGeometricObjects/HitObject.h"

double HitObject::calcNorm(const Point3 &point, const Vector3 &vector) const {
    return point.point.head<3>().dot(vector.vector.head<3>());
}

double HitObject::calcNorm(const Vector3 &vector1, const Vector3 &vector2) const {
    return vector1.vector.head<3>().dot(vector2.vector.head<3>());
}

double HitObject::calcNorm(const Point3 &point1, const Point3 &point2) const {
    return point1.point.head<3>().dot(point2.point.head<3>());
}

double HitObject::calcNorm(const Eigen::Vector3d &vector1, const Eigen::Vector3d &vector2) const {
    return vector1.dot(vector2);
}


void HitObject::transformRayToObjectSpace(const Ray& incomingRay, Ray &genRay) const {

    genRay.dir.vector = inverseTransform * incomingRay.dir.vector;
    genRay.start.point = inverseTransform * incomingRay.start.point;
}

const Eigen::Matrix4d &HitObject::getInverseTransform() const {
    return inverseTransform;
}

const Eigen::Matrix4d &HitObject::getTransform() const {
    return transform;
}

HitObject::HitObject(const std::shared_ptr<AbstractMaterial> &material) : material(material) {}



