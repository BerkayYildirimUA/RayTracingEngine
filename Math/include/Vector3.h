//
// Created by berka on 08/10/2024.
//

#ifndef RAYTRACINGENGINE_VECTOR3_H
#define RAYTRACINGENGINE_VECTOR3_H


#include "Point3.h"
#include "Eigen/Core"
#include "GeometricFunctionsLookup.h"

class Vector3 {

public:
    Eigen::Vector4d vector;

    void set(double new_x, double new_y, double new_z) { vector.x() = new_x; vector.y() = new_y; vector.z() = new_z;}

    void set(Vector3 & newVector) { vector.x() = newVector.vector.x(); vector.y() = newVector.vector.y(); vector.z() = newVector.vector.z();}
    void set(Vector3 && newVector) { vector = std::move(newVector.vector);}

    void set(const Eigen::Vector3d & newVector) { this->set(newVector.x(), newVector.y(), newVector.z());};


    Vector3(double x, double y, double z) { vector << x, y, z, 0;}

    Vector3() { vector << 0, 0, 0, 0;}

    Vector3(Vector3 &vec) {vector << vec.vector.x(), vec.vector.y(), vec.vector.z(), 0;}
    explicit Vector3(Eigen::Vector3d &vec) {vector << vec.x(), vec.y(), vec.z(), 0;}


    explicit Vector3(Eigen::Vector4d&& cords) {vector = std::move(cords);}

    void normalize(){
        vector.head(3).normalize();
    }

    double angleBetweenInRadians(const Vector3& other) const {
        Eigen::Vector3d myVec = vector.head(3);
        Eigen::Vector3d otherVec = other.vector.head(3);

        double dotProduct = myVec.dot(otherVec);
        double magnitudes = myVec.norm() * otherVec.norm();

        if (magnitudes == 0) {
            return 0;
        }

        double cosTheta = dotProduct / magnitudes;

        cosTheta = std::max(-1.0, std::min(1.0, cosTheta));



        return GeometricFunctionsLookup::getAcos(cosTheta);
    }

    Vector3 operator+(const Vector3 &other) const {
        Eigen::Vector3d temp = this->vector.head(3) + other.vector.head(3);
        return Vector3(temp);
    }

    double operator*(const Vector3 &other) const {
        return this->vector.head(3).dot(other.vector.head(3));
    }

    Vector3 operator*(const double &other) const {
        return {this->vector.x() * other, this->vector.y() * other, this->vector.z() * other};
    }

    friend Vector3 operator*(double scalar, const Vector3& obj);


    Vector3 operator*(const int &other) const {
        return {this->vector.x() * other, this->vector.y() * other, this->vector.z() * other};
    }

    Vector3 operator-(const Vector3 &other) const {
        return {this->vector.x() - other.getX(), this->vector.y() - other.getY(), this->vector.z() - other.getZ()};
    }

    Vector3 operator-(const Eigen::Vector3d &other) const {
        return {this->vector.x() - other.x(), this->vector.y() - other.y(), this->vector.z() - other.z()};
    }

    Vector3 operator+(const Eigen::Vector3d &other) const {
        return {this->vector.x() + other.x(), this->vector.y() + other.y(), this->vector.z() + other.z()};
    }

    Vector3 operator-() const {
        return {-vector.x(), -vector.y(), -vector.z()};
    }

    double getX() const{
        return vector.x();
    }


    double getY() const{
        return vector.y();
    }


    double getZ() const{
        return vector.z();
    }

    void getRidOfVerySmallNumber(){
        double threshold = 1;
        vector = vector.unaryExpr([threshold](double x) {
            return std::abs(x) < threshold ? 0 : x;
        });
    }
};







#endif //RAYTRACINGENGINE_VECTOR3_H
