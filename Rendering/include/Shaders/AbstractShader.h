//
// Created by berka on 27/10/2024.
//

#ifndef RAYTRACINGENGINE_ABSTRACTSHADER_H
#define RAYTRACINGENGINE_ABSTRACTSHADER_H

#include "Ray.h"
#include "Color3.h"
#include "Intersection.h"
#include "LightSource.h"
#include "Material/AbstractMaterial.h"

class AbstractShader {
public:
    virtual Color3 shade(Ray &ray, Intersection &best, const std::vector<std::shared_ptr<LightSource>>& lightSources, std::shared_ptr<AbstractMaterial> &material) = 0;

};


#endif //RAYTRACINGENGINE_ABSTRACTSHADER_H
