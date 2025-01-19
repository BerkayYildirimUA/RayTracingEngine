//
// Created by berka on 22/10/2024.
//

#include "Rendering/include/Shaders/Material/FresnelMaterial.h"


FresnelMaterial::FresnelMaterial(double normalReflectanceRed, double normalReflectanceGreen,
                                 double normalReflectanceBlue, double ambientLightFactor, double defusedLightFactor,
                                 double roughness) : roughness(roughness), ambientLightFactor(ambientLightFactor),
                                                     defusedLightFactor(defusedLightFactor),
                                                     specularLightFactor(1 - defusedLightFactor) {

    indexOfRefraction.x() = (1 + sqrt(normalReflectanceRed)) / (1 - sqrt(normalReflectanceRed));
    indexOfRefraction.y() = (1 + sqrt(normalReflectanceGreen)) / (1 - sqrt(normalReflectanceGreen));
    indexOfRefraction.z() = (1 + sqrt(normalReflectanceBlue)) / (1 - sqrt(normalReflectanceBlue));

    indexOfRefraction = indexOfRefraction.cwiseMin(100000.0);
}

const Eigen::Vector3d &FresnelMaterial::getIndexOfRefraction() const {
    return indexOfRefraction;
}

const double &FresnelMaterial::getIndexOfRefractionByIndex(int i) const {
    return indexOfRefraction[i];
}

FresnelMaterial::FresnelMaterial(double normalReflectanceRed, double normalReflectanceGreen,
                                 double normalReflectanceBlue, double ambientLightFactor, double defusedLightFactor,
                                 double roughness, double transparency, double shininess, double speedOfLight)
        : FresnelMaterial(normalReflectanceRed, normalReflectanceGreen, normalReflectanceBlue,
                          ambientLightFactor, defusedLightFactor, roughness) {


    this->shininess = shininess;
    this->transparency = transparency;
    this->speedOfLight = speedOfLight;

}


/*
Eigen::Vector3d FresnelMaterial::calcFresnalCoefficient(double angleInDegrees) {

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


