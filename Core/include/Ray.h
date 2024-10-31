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
    void setStart(Point3 &&newStart);
    void setDir(Vector3 &&newDir);
    Eigen::Matrix<double, 3, 1> calcPoint(double t) const;

    void setStart(double x, double y, double z){
        start.set(x, y, z);
    }

    void setStart(const Point3 &start);

    void setDir(const Vector3 &dir);

    void setDir(double x, double y, double z){
        dir.set(x, y, z);
    }


    Ray(Point3 &&startPoint, Vector3 &&direction){start = std::move(startPoint); dir = std::move(direction);}
    Ray(Point3 &startPoint, Vector3 &direction){start = std::move(startPoint); dir = std::move(direction);}

    Ray(){start = Point3(); dir = Vector3();}
};


#endif //RAYTRACINGENGINE_RAY_H
