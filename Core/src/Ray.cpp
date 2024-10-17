//
// Created by berka on 07/10/2024.
//

#include "Core/include/Ray.h"

void Ray::setStart(Point3 &&newStart) {
    this->start = std::move(newStart);
}

void Ray::setDir(Vector3 &&newDir) {
    this->dir = std::move(newDir);
}

Eigen::Matrix<double, 3, 1> Ray::calcPoint(double t) {
    return start.point.head<3>() + dir.vector.head<3>()*t ;
}
