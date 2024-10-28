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

    Vector3(Vector3 &vec) {vector << vec.vector.x(), vec.vector.y(), vec.vector.z(), 0;}
    explicit Vector3(Eigen::Vector3d &vec) {vector << vec.x(), vec.y(), vec.z(), 0;}


    explicit Vector3(Eigen::Vector4d&& cords) {vector = std::move(cords);}

    void normilze(){
        vector.head(3).normalize();
    }

    double angleBetweenInRadians(const Vector3& other) const {
        double dotProduct = vector.head(3).dot(other.vector.head(3));
        double magnitudes = vector.head(3).norm() * other.vector.head(3).norm();

        if (magnitudes == 0) return 0;

        double cosTheta = dotProduct / magnitudes;

        cosTheta = std::max(-1.0, std::min(1.0, cosTheta));

        return std::acos(cosTheta);
    }

    Vector3 operator+(const Vector3 &other) const {
        Eigen::Vector3d temp = this->vector.head(3) + other.vector.head(3);
        return Vector3(temp);
    }

    double operator*(const Vector3 &other) const {
        return this->vector.head(3).dot(other.vector.head(3));
    }


};






#endif //RAYTRACINGENGINE_VECTOR3_H
