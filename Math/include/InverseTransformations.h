//
// Created by berka on 10/10/2024.
//

#ifndef RAYTRACINGENGINE_INVERSETRANSFORMATIONS_H
#define RAYTRACINGENGINE_INVERSETRANSFORMATIONS_H

#include "Eigen/Core"
#include "Point3.h"
#include "Transformations.h"

class InverseTransformations {
public:
    static Eigen::Vector4d inverseTranslation(Eigen::Vector4d &point, double x, double y, double z){
        return Transformations::translatePoint(point, -x, -y, -z);
    };

    static Eigen::Vector4d inverseScaling(Eigen::Vector4d &point, double x, double y, double z){
        return Transformations::scalePoint(point, 1/x, 1/y, 1/z);
    };

    static Eigen::Vector4d inverseRotationX(Eigen::Vector4d &point, double angle){
        return Transformations::rotatePointX(point, -angle);
    };

    static Eigen::Vector4d inverseRotationY(Eigen::Vector4d &point, double angle){
        return Transformations::rotatePointY(point, -angle);
    }

    static Eigen::Vector4d inverseRotationZ(Eigen::Vector4d &point, double angle){
        return Transformations::rotatePointZ(point, -angle);
    }

    // Create transformation matrices
    static Eigen::Matrix4d createInverseTranslationMatrix(double x, double y, double z){
        return Transformations::createTranslationMatrix(-x, -y, -z);
    }
    static Eigen::Matrix4d createInverseScalingMatrix(double x, double y, double z){
        return Transformations::createScalingMatrix(1/x, 1/y, 1/z);
    }
    static Eigen::Matrix4d createInverseRotationMatrixX(double angle){
        return Transformations::createRotationMatrixX(-angle);
    }
    static Eigen::Matrix4d createInverseRotationMatrixY(double angle){
        return Transformations::createRotationMatrixY(-angle);
    }
    static Eigen::Matrix4d createInverseRotationMatrixZ(double angle){
        return Transformations::createRotationMatrixZ(-angle);
    }

    // Combine transformations
    static Eigen::Matrix4d applyInverseTranslation(const Eigen::Matrix4d& matrix, double x, double y, double z) {
        return createInverseTranslationMatrix(x, y, z) * matrix;
    }

    static Eigen::Matrix4d applyInverseScaling(const Eigen::Matrix4d& matrix, double x, double y, double z) {
        return createInverseScalingMatrix(x, y, z) * matrix;
    }

    static Eigen::Matrix4d applyInverseRotationX(const Eigen::Matrix4d& matrix, double angle) {
        return createInverseRotationMatrixX(angle) * matrix;
    }

    static Eigen::Matrix4d applyInverseRotationY(const Eigen::Matrix4d& matrix, double angle) {
        return createInverseRotationMatrixY(angle) * matrix;
    }

    static Eigen::Matrix4d applyInverseRotationZ(const Eigen::Matrix4d& matrix, double angle) {
        return createInverseRotationMatrixZ(angle) * matrix;
    }

};


#endif //RAYTRACINGENGINE_INVERSETRANSFORMATIONS_H
