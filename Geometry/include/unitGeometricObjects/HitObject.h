//
// Created by berka on 10/10/2024.
//

#ifndef RAYTRACINGENGINE_HITOBJECT_H
#define RAYTRACINGENGINE_HITOBJECT_H

#include "Core/include/Ray.h"
#include "Geometry/include/Intersection.h"
#include "Math/include/Transformations.h"
#include "memory"

class Intersection;

class HitObject : public std::enable_shared_from_this<HitObject> {
public:

    virtual bool hit(const Ray &incomingRay, Intersection& intersection) = 0;

protected:
    Eigen::Matrix4d inverseTransform = Eigen::Matrix4d::Identity();
    Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
    Ray genRay = Ray();

    void transformRayToObjectSpace (const Ray& incomingRay);

    double calcNorm(const Point3 &point, const Vector3 &vector) const;
    double calcNorm(const Vector3 &vector1, const Vector3 &vector2) const;
    double calcNorm(const Point3 &point1, const Point3 &point2) const;
    double calcNorm(const Eigen::Vector3d &vector1, const Eigen::Vector3d &vector2) const;

};


#endif //RAYTRACINGENGINE_HITOBJECT_H
