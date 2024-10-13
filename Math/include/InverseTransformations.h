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
    static Eigen::Matrix<double, 4, 1> inverseTranslation(Eigen::Matrix<double, 4, 1> &point, double x, double y, double z){
        return Transformations::translatePoint(point, -x, -y, -z);
    };

    static Eigen::Matrix<double, 4, 1> inverseScaling(Eigen::Matrix<double, 4, 1> &point, double x, double y, double z){
        return Transformations::scalePoint(point, 1/x, 1/y, 1/z);
    };

    static Eigen::Matrix<double, 4, 1> inverseRotationX(Eigen::Matrix<double, 4, 1> &point, double angle){
        return Transformations::rotatePointX(point, -angle);
    };

    static Eigen::Matrix<double, 4, 1> inverseRotationY(Eigen::Matrix<double, 4, 1> &point, double angle){
        return Transformations::rotatePointY(point, -angle);
    }

    static Eigen::Matrix<double, 4, 1> inverseRotationZ(Eigen::Matrix<double, 4, 1> &point, double angle){
        return Transformations::rotatePointZ(point, -angle);
    }

    // Create transformation matrices
    static Eigen::Matrix<double, 4, 4> createInverseTranslationMatrix(double x, double y, double z){
        return Transformations::createTranslationMatrix(-x, -y, -z);
    }
    static Eigen::Matrix<double, 4, 4> createInverseScalingMatrix(double x, double y, double z){
        return Transformations::createScalingMatrix(-x, -y, -z);
    }
    static Eigen::Matrix<double, 4, 4> createInverseRotationMatrixX(double angle){
        return Transformations::createRotationMatrixX(angle);
    }
    static Eigen::Matrix<double, 4, 4> createInverseRotationMatrixY(double angle){
        return Transformations::createRotationMatrixY(angle);
    }
    static Eigen::Matrix<double, 4, 4> createInverseRotationMatrixZ(double angle){
        return Transformations::createRotationMatrixZ(angle);
    }

    // Combine transformations
    static Eigen::Matrix<double, 4, 4> applyInverseTranslation(const Eigen::Matrix<double, 4, 4>& matrix, double x, double y, double z) {
        return createInverseTranslationMatrix(x, y, z) * matrix;
    }

    static Eigen::Matrix<double, 4, 4> applyInverseScaling(const Eigen::Matrix<double, 4, 4>& matrix, double x, double y, double z) {
        return createInverseScalingMatrix(x, y, z) * matrix;
    }

    static Eigen::Matrix<double, 4, 4> applyInverseRotationX(const Eigen::Matrix<double, 4, 4>& matrix, double angle) {
        return createInverseRotationMatrixX(angle) * matrix;
    }

    static Eigen::Matrix<double, 4, 4> applyInverseRotationY(const Eigen::Matrix<double, 4, 4>& matrix, double angle) {
        return createInverseRotationMatrixY(angle) * matrix;
    }

    static Eigen::Matrix<double, 4, 4> applyInverseRotationZ(const Eigen::Matrix<double, 4, 4>& matrix, double angle) {
        return createInverseRotationMatrixZ(angle) * matrix;
    }

};


#endif //RAYTRACINGENGINE_INVERSETRANSFORMATIONS_H
