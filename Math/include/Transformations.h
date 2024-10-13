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
    static Eigen::Matrix<double, 4, 1> translatePoint(const Eigen::Matrix<double, 4, 1>& point, double x, double y, double z);
    static Eigen::Matrix<double, 4, 1> scalePoint(const Eigen::Matrix<double, 4, 1>& point, double x, double y, double z);
    static Eigen::Matrix<double, 4, 1> rotatePointX(const Eigen::Matrix<double, 4, 1>& point, double angle);
    static Eigen::Matrix<double, 4, 1> rotatePointY(const Eigen::Matrix<double, 4, 1>& point, double angle);
    static Eigen::Matrix<double, 4, 1> rotatePointZ(const Eigen::Matrix<double, 4, 1>& point, double angle);

    // Create transformation matrices
    static Eigen::Matrix<double, 4, 4> createTranslationMatrix(double x, double y, double z);
    static Eigen::Matrix<double, 4, 4> createScalingMatrix(double x, double y, double z);
    static Eigen::Matrix<double, 4, 4> createRotationMatrixX(double angle);
    static Eigen::Matrix<double, 4, 4> createRotationMatrixY(double angle);
    static Eigen::Matrix<double, 4, 4> createRotationMatrixZ(double angle);

    // Combine transformations
    static Eigen::Matrix<double, 4, 4> applyTranslation(const Eigen::Matrix<double, 4, 4>& matrix, double x, double y, double z);
    static Eigen::Matrix<double, 4, 4> applyScaling(const Eigen::Matrix<double, 4, 4>& matrix, double x, double y, double z);
    static Eigen::Matrix<double, 4, 4> applyRotationX(const Eigen::Matrix<double, 4, 4>& matrix, double angle);
    static Eigen::Matrix<double, 4, 4> applyRotationY(const Eigen::Matrix<double, 4, 4>& matrix, double angle);
    static Eigen::Matrix<double, 4, 4> applyRotationZ(const Eigen::Matrix<double, 4, 4>& matrix, double angle);


private:
    static double degreeToRad(double degree);

};


#endif //RAYTRACINGENGINE_TRANSFERFUNCTIONS_H
