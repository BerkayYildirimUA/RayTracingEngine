//
// Created by berka on 27/10/2024.
//

#ifndef RAYTRACINGENGINE_ABSTRACTMATERIAL_H
#define RAYTRACINGENGINE_ABSTRACTMATERIAL_H

#include <functional>
#include "Color3.h"
#include "Math/include/Point3.h"

class AbstractMaterial {
protected:
    std::function<Color3(double, double, double)> textureFunction;

public:
    double transparency = 0;
    double shininess = 0;
    double speedOfLight = 1000;


    AbstractMaterial(double transparency, double shininess, double speedOfLight);

    AbstractMaterial();

    virtual ~AbstractMaterial() = default;

    void setTextureFunction(const std::function<Color3(double, double, double)> &func);
    Color3 getTexture(double x, double y, double z) const;

    Color3 getTexture(Point3 point) const;
};


#endif //RAYTRACINGENGINE_ABSTRACTMATERIAL_H
