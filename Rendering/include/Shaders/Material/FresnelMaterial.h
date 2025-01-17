//
// Created by berka on 22/10/2024.
//

#ifndef RAYTRACINGENGINE_FRESNELMATERIAL_H
#define RAYTRACINGENGINE_FRESNELMATERIAL_H

#include "Eigen/Core"
#include "Color3.h"
#include "AbstractMaterial.h"
#include <functional>

class FresnelMaterial : public AbstractMaterial{

private:
    Eigen::Vector3d indexOfRefraction;
    std::function<Color3(double, double, double)> textureFunction;

public:
    double defusedLightFactor;
    double specularLightFactor;
    double roughness;
    double ambientLightFactor;

    FresnelMaterial(double normalReflectanceRed, double normalReflectanceGreen, double normalReflectanceBlue, double ambientLightFactor, double defusedLightFactor, double roughness);

    FresnelMaterial(double normalReflectanceRed, double normalReflectanceGreen, double normalReflectanceBlue, double ambientLightFactor, double defusedLightFactor, double roughness, double transparency, double shininess, double speedOfLight);


    const Eigen::Vector3d &getIndexOfRefraction() const;

    const double &getIndexOfRefractionByIndex(int i) const;

    void setTextureFunction(const std::function<Color3(double, double, double)> &func);
    Color3 getTexture(double x, double y, double z) const;

};


#endif //RAYTRACINGENGINE_FRESNELMATERIAL_H
