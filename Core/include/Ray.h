//
// Created by berka on 07/10/2024.
//

#ifndef RAYTRACINGENGINE_RAY_H
#define RAYTRACINGENGINE_RAY_H

#include "Math/include/Point3.h"
#include "Math/include/Vector3.h"
#include "Eigen/Core"


class Ray {
public:
    Point3 start;
    Vector3 dir;
    void setStart(const Point3 &start);
    void setDir(const Vector3 &dir);
    Eigen::Matrix<double, 3, 1> calcPoint(double t);
    Ray(Point3 startPoint, Vector3 direction){start = startPoint; dir = direction;}
    Ray(){start = Point3(); dir = Vector3();}
};


#endif //RAYTRACINGENGINE_RAY_H
