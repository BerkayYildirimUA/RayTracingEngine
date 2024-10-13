//
// Created by berka on 08/10/2024.
//

#include "Math/include/Transformations.h"
#include <cmath>

Eigen::Matrix<double, 4, 1>
Transformations::translatePoint(const Eigen::Matrix<double, 4, 1> &point, double x, double y, double z) {
    return createTranslationMatrix(x, y, z) * point;
}

Eigen::Matrix<double, 4, 1>
Transformations::scalePoint(const Eigen::Matrix<double, 4, 1> &point, double x, double y, double z) {
    return createScalingMatrix(x, y, z) * point;
}

Eigen::Matrix<double, 4, 1> Transformations::rotatePointX(const Eigen::Matrix<double, 4, 1> &point, double angle) {
    return createRotationMatrixX(angle) * point;
}

Eigen::Matrix<double, 4, 1> Transformations::rotatePointY(const Eigen::Matrix<double, 4, 1> &point, double angle) {
    return createRotationMatrixY(angle) * point;
}

Eigen::Matrix<double, 4, 1> Transformations::rotatePointZ(const Eigen::Matrix<double, 4, 1> &point, double angle) {
    return createRotationMatrixZ(angle) * point;
}

double Transformations::degreeToRad(double degree) {

    return degree * (M_PI / 180);
}

Eigen::Matrix<double, 4, 4> Transformations::createTranslationMatrix(double x, double y, double z) {
    Eigen::Matrix<double, 4, 4> transferMatrix;
    transferMatrix << 1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1;

    return transferMatrix;
}

Eigen::Matrix<double, 4, 4> Transformations::createScalingMatrix(double x, double y, double z) {
    Eigen::Matrix<double, 4, 4> transferMatrix;
    transferMatrix << x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, 0,
            0, 0, 0, 1;

    return transferMatrix;
}

Eigen::Matrix<double, 4, 4> Transformations::createRotationMatrixX(double angle) {
    double rad = degreeToRad(angle);
    double c = std::cos(rad);
    double s = std::sin(rad);

    Eigen::Matrix<double, 4, 4> transferMatrix;
    transferMatrix << 1, 0, 0, 0,
            0, c, -s, 0,
            0, s, c, 0,
            0, 0, 0, 1;

    return transferMatrix;
}

Eigen::Matrix<double, 4, 4> Transformations::createRotationMatrixY(double angle) {
    double rad = degreeToRad(angle);
    double c = std::cos(rad);
    double s = std::sin(rad);

    Eigen::Matrix<double, 4, 4> transferMatrix;
    transferMatrix << c, 0, s, 0,
            0, 1, 0, 0,
            -s, 0, c, 0,
            0, 0, 0, 1;

    return transferMatrix;
}

Eigen::Matrix<double, 4, 4> Transformations::createRotationMatrixZ(double angle) {
    double rad = degreeToRad(angle);
    double c = std::cos(rad);
    double s = std::sin(rad);

    Eigen::Matrix<double, 4, 4> transferMatrix;
    transferMatrix << c, -s, 0, 0,
            s, c, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1;

    return transferMatrix;
}

Eigen::Matrix<double, 4, 4>
Transformations::applyTranslation(const Eigen::Matrix<double, 4, 4> &matrix, double x, double y, double z) {
    return createTranslationMatrix(x, y, z) * matrix;
}

Eigen::Matrix<double, 4, 4>
Transformations::applyScaling(const Eigen::Matrix<double, 4, 4> &matrix, double x, double y, double z) {
    return createScalingMatrix(x, y, z) * matrix;
}

Eigen::Matrix<double, 4, 4> Transformations::applyRotationX(const Eigen::Matrix<double, 4, 4> &matrix, double angle) {
    return createRotationMatrixX(angle) * matrix;
}

Eigen::Matrix<double, 4, 4> Transformations::applyRotationY(const Eigen::Matrix<double, 4, 4> &matrix, double angle) {
    return createRotationMatrixY(angle) * matrix;
}

Eigen::Matrix<double, 4, 4> Transformations::applyRotationZ(const Eigen::Matrix<double, 4, 4> &matrix, double angle) {
    return createRotationMatrixZ(angle) * matrix;
}
