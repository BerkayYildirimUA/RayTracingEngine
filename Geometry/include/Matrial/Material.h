//
// Created by berka on 22/10/2024.
//

#ifndef RAYTRACINGENGINE_MATERIAL_H
#define RAYTRACINGENGINE_MATERIAL_H

#include "Eigen/Core"
#include "Color3.h"

class Material {

    double defusedLightFactor;
    double specularLightFactor;

    Eigen::Vector3d indexOfRefraction;

public:
    Material(double normalReflectanceRed, double normalReflectanceGreen, double normalReflectanceBlue, double defusedLightFactor);

    Eigen::Vector3d calcFresnelCoefficient(double angleInDegrees);
    double calcFresnelCoefficientForColor(double angleInDegrees, double indexOfRefraction);
};


#endif //RAYTRACINGENGINE_MATERIAL_H
