//
// Created by berka on 08/10/2024.
//

#include "Eigen/Core"
#include "Point3.h"

#ifndef RAYTRACINGENGINE_TRANSFERFUNCTIONS_H
#define RAYTRACINGENGINE_TRANSFERFUNCTIONS_H


class Transformations {

public:
    // Transform points
    static Eigen::Vector4d translatePoint(const Eigen::Vector4d& point, double x, double y, double z);
    static Eigen::Vector4d scalePoint(const Eigen::Vector4d& point, double x, double y, double z);
    static Eigen::Vector4d rotatePointX(const Eigen::Vector4d& point, double angle);
    static Eigen::Vector4d rotatePointY(const Eigen::Vector4d& point, double angle);
    static Eigen::Vector4d rotatePointZ(const Eigen::Vector4d& point, double angle);

    // Create transformation matrices
    static Eigen::Matrix4d createTranslationMatrix(double x, double y, double z);
    static Eigen::Matrix4d createScalingMatrix(double x, double y, double z);
    static Eigen::Matrix4d createRotationMatrixX(double angle);
    static Eigen::Matrix4d createRotationMatrixY(double angle);
    static Eigen::Matrix4d createRotationMatrixZ(double angle);

    // Combine transformations
    static Eigen::Matrix4d applyTranslation(const Eigen::Matrix4d& matrix, double x, double y, double z);
    static Eigen::Matrix4d applyScaling(const Eigen::Matrix4d& matrix, double x, double y, double z);
    static Eigen::Matrix4d applyRotationX(const Eigen::Matrix4d& matrix, double angle);
    static Eigen::Matrix4d applyRotationY(const Eigen::Matrix4d& matrix, double angle);
    static Eigen::Matrix4d applyRotationZ(const Eigen::Matrix4d& matrix, double angle);


    static double degreeToRad(double degree);

};


#endif //RAYTRACINGENGINE_TRANSFERFUNCTIONS_H
