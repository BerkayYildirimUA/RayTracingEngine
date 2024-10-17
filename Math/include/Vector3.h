//
// Created by berka on 08/10/2024.
//

#ifndef RAYTRACINGENGINE_VECTOR3_H
#define RAYTRACINGENGINE_VECTOR3_H


#include "Point3.h"
#include "Eigen/Core"

class Vector3 {

public:
    Eigen::Vector4d vector;

    void set(double new_x, double new_y, double new_z) { vector << new_x, new_y, new_z, 0;}

    void set(Vector3 & newVector) { vector = newVector.vector;}
    void set(Vector3 && newVector) { vector = std::move(newVector.vector);}

    Vector3(double x, double y, double z) { vector << x, y, z, 0;}

    Vector3() { vector << 0, 0, 0, 0;}
    explicit Vector3(Eigen::Vector4d&& cords) {vector = std::move(cords);}

};






#endif //RAYTRACINGENGINE_VECTOR3_H
