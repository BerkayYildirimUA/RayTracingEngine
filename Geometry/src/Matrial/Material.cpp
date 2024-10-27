//
// Created by berka on 22/10/2024.
//

#include "Geometry/include/Matrial/Material.h"
#include "math.h"
#include "thread"

Material::Material(double normalReflectanceRed, double normalReflectanceGreen, double normalReflectanceBlue,
                   double defusedLightFactor) {
    indexOfRefraction.x() = (1 + sqrt(normalReflectanceRed)) / (1 - sqrt(normalReflectanceRed));
    indexOfRefraction.y() = (1 + sqrt(normalReflectanceGreen)) / (1 - sqrt(normalReflectanceGreen));
    indexOfRefraction.z() = (1 + sqrt(normalReflectanceBlue)) / (1 - sqrt(normalReflectanceBlue));
    this->defusedLightFactor = defusedLightFactor;
    this->specularLightFactor = 1 - defusedLightFactor;
}
/*
Eigen::Vector3d Material::calcFresnalCoefficient(double angleInDegrees) {

    if (angleInDegrees == 0) {
        Eigen::Vector3d up = (indexOfRefraction - Eigen::Vector3d(1, 1, 1));
        Eigen::Vector3d down = (indexOfRefraction + Eigen::Vector3d(1, 1, 1));
        return up.cwiseProduct(up).cwiseQuotient(down.cwiseProduct(down));
    }

    double radians = (angleInDegrees/180) * EIGEN_PI;

    Eigen::Vector3d vectorOfOnes(1, 1, 1);

    double c = cos(radians);
    Eigen::Vector3d g = (indexOfRefraction.cwiseProduct(indexOfRefraction) + Eigen::Vector3d(c*c, c*c, c*c) - vectorOfOnes).cwiseSqrt();

    Eigen::Vector3d gMinusC = g - Eigen::Vector3d(c, c, c);
    Eigen::Vector3d gPlusC = g + Eigen::Vector3d(c, c, c);

    Eigen::Vector3d firstTerm = 0.5 * gMinusC.cwiseProduct(gMinusC).cwiseQuotient(gPlusC.cwiseProduct(gPlusC));

    Eigen::Vector3d secondTerm = (c*gPlusC - vectorOfOnes).cwiseQuotient(c*gMinusC + vectorOfOnes);
    secondTerm = vectorOfOnes + secondTerm.cwiseProduct(secondTerm);

    return firstTerm.cwiseProduct(secondTerm);
}*/

Eigen::Vector3d Material::calcFresnelCoefficient(double angleInDegrees) {
    Eigen::Vector3d fresnelCoefficient;

    std::thread redThread([&]() { fresnelCoefficient[0] = calcFresnelCoefficientForColor(angleInDegrees, indexOfRefraction[0]); });
    std::thread greenThread([&]() { fresnelCoefficient[1] = calcFresnelCoefficientForColor(angleInDegrees, indexOfRefraction[1]); });
    std::thread blueThread([&]() { fresnelCoefficient[2] = calcFresnelCoefficientForColor(angleInDegrees, indexOfRefraction[2]); });

    redThread.join();
    greenThread.join();
    blueThread.join();

    return fresnelCoefficient;
}

double Material::calcFresnelCoefficientForColor(double angleInDegrees, double indexOfRefraction) {
    if (angleInDegrees == 0) {
        double up = indexOfRefraction - 1.0;
        double down = indexOfRefraction + 1.0;
        return (up * up) / (down * down);
    }

    double radians = (angleInDegrees / 180) * EIGEN_PI;
    double c = cos(radians);
    double g = sqrt(indexOfRefraction * indexOfRefraction + c * c - 1);

    double gMinusC = g - c;
    double gPlusC = g + c;

    double firstTerm = 0.5 * (gMinusC * gMinusC) / (gPlusC * gPlusC);
    double secondTerm = (c * gPlusC - 1) / (c * gMinusC + 1);
    secondTerm = 1 + secondTerm * secondTerm;

    return firstTerm * secondTerm;
}
