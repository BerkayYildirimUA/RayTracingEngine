//
// Created by berka on 08/10/2024.
//

#include "Math/include/Transformations.h"
#include <cmath>

Eigen::Vector4d
Transformations::translatePoint(const Eigen::Vector4d &point, double x, double y, double z) {
    return createTranslationMatrix(x, y, z) * point;
}

Eigen::Vector4d
Transformations::scalePoint(const Eigen::Vector4d &point, double x, double y, double z) {
    return createScalingMatrix(x, y, z) * point;
}

Eigen::Vector4d Transformations::rotatePointX(const Eigen::Vector4d &point, double angle) {
    return createRotationMatrixX(angle) * point;
}

Eigen::Vector4d Transformations::rotatePointY(const Eigen::Vector4d &point, double angle) {
    return createRotationMatrixY(angle) * point;
}

Eigen::Vector4d Transformations::rotatePointZ(const Eigen::Vector4d &point, double angle) {
    return createRotationMatrixZ(angle) * point;
}

double Transformations::degreeToRad(double degree) {

    return degree * (EIGEN_PI / 180.0);
}

Eigen::Matrix4d Transformations::createTranslationMatrix(double x, double y, double z) {
    Eigen::Matrix4d transferMatrix;
    transferMatrix << 1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1;

    return transferMatrix;
}

Eigen::Matrix4d Transformations::createScalingMatrix(double x, double y, double z) {
    Eigen::Matrix4d transferMatrix;
    transferMatrix << x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, 0,
            0, 0, 0, 1;

    return transferMatrix;
}

Eigen::Matrix4d Transformations::createRotationMatrixX(double angle) {
    double rad = degreeToRad(angle);
    double c = std::cos(rad);
    double s = std::sin(rad);

    Eigen::Matrix4d transferMatrix;
    transferMatrix << 1, 0, 0, 0,
            0, c, -s, 0,
            0, s, c, 0,
            0, 0, 0, 1;

    return transferMatrix;
}

Eigen::Matrix4d Transformations::createRotationMatrixY(double angle) {
    double rad = degreeToRad(angle);
    double c = std::cos(rad);
    double s = std::sin(rad);

    Eigen::Matrix4d transferMatrix;
    transferMatrix << c, 0, s, 0,
            0, 1, 0, 0,
            -s, 0, c, 0,
            0, 0, 0, 1;

    return transferMatrix;
}

Eigen::Matrix4d Transformations::createRotationMatrixZ(double angle) {
    double rad = degreeToRad(angle);
    double c = std::cos(rad);
    double s = std::sin(rad);

    Eigen::Matrix4d transferMatrix;
    transferMatrix << c, -s, 0, 0,
            s, c, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1;

    return transferMatrix;
}

Eigen::Matrix4d
Transformations::applyTranslation(const Eigen::Matrix4d &matrix, double x, double y, double z) {
    return createTranslationMatrix(x, y, z) * matrix;
}

Eigen::Matrix4d
Transformations::applyScaling(const Eigen::Matrix4d &matrix, double x, double y, double z) {
    return createScalingMatrix(x, y, z) * matrix;
}

Eigen::Matrix4d Transformations::applyRotationX(const Eigen::Matrix4d &matrix, double angle) {
    return createRotationMatrixX(angle) * matrix;
}

Eigen::Matrix4d Transformations::applyRotationY(const Eigen::Matrix4d &matrix, double angle) {
    return createRotationMatrixY(angle) * matrix;
}

Eigen::Matrix4d Transformations::applyRotationZ(const Eigen::Matrix4d &matrix, double angle) {
    return createRotationMatrixZ(angle) * matrix;
}
