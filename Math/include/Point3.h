//
// Created by berka on 08/10/2024.
//

#ifndef RAYTRACINGENGINE_POINT3_H
#define RAYTRACINGENGINE_POINT3_H


#include "Eigen/Core"

class Point3 {

public:
    Eigen::Vector4d point;

    void set(double new_x, double new_y, double new_z) { point << new_x, new_y, new_z, 1; }

    void set(Point3 &newPoint) { point = newPoint.point; }

    Point3(double x, double y, double z) { point << x, y, z, 1; }

    Point3() { point << 0, 0, 0, 1; }

    explicit Point3(Eigen::Vector4d&& cords) {    point = std::move(cords);}

    double operator*(const Point3 &other) const {
        return this->point.head(3).dot(other.point.head(3));
    }

};


#endif //RAYTRACINGENGINE_POINT3_H
