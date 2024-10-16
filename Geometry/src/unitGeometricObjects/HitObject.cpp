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

Ray HitObject::transformRayToObjectSpace(const Ray& ray) const {

    Point3 newStart(inverseTransform * ray.start.point);
    Vector3 newDir(inverseTransform * ray.dir.vector);

    Ray newRay(std::move(newStart), std::move(newDir));


    return std::move(newRay);
}


