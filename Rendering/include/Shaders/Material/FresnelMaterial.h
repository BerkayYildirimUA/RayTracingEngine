//
// Created by berka on 22/10/2024.
//

#ifndef RAYTRACINGENGINE_FRESNELMATERIAL_H
#define RAYTRACINGENGINE_FRESNELMATERIAL_H

#include "Eigen/Core"
#include "Color3.h"
#include "AbstractMaterial.h"

class FresnelMaterial : public AbstractMaterial{

    Eigen::Vector3d indexOfRefraction;

public:
    double defusedLightFactor;
    double specularLightFactor;
    double roughness;
    double ambientLightFactor;

    FresnelMaterial(double normalReflectanceRed, double normalReflectanceGreen, double normalReflectanceBlue, double ambientLightFactor, double defusedLightFactor, double roughness);

    FresnelMaterial(double normalReflectanceRed, double normalReflectanceGreen, double normalReflectanceBlue, double ambientLightFactor, double defusedLightFactor, double roughness, double transparency, double shininess, double speedOfLight);


    const Eigen::Vector3d &getIndexOfRefraction() const;

    const double &getIndexOfRefractionByIndex(int i) const;

};


#endif //RAYTRACINGENGINE_FRESNELMATERIAL_H
