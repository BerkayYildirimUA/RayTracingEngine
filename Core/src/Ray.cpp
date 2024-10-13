//
// Created by berka on 07/10/2024.
//

#include "Core/include/Ray.h"

void Ray::setStart(const Point3 &start) {

}

void Ray::setDir(const Vector3 &dir) {

}

Eigen::Matrix<double, 3, 1> Ray::calcPoint(double t) {
    return start.point.head<3>() + dir.vector.head<3>()*t ;
}
