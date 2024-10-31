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
    virtual Color3 shade(const Ray &ray, Intersection &best, const std::shared_ptr<LightSource>& lightSources, std::shared_ptr<AbstractMaterial> &material) = 0;

    virtual Color3 getAmbientPart(const std::shared_ptr<LightSource> &lightSource,
                                  const std::shared_ptr<AbstractMaterial> &material) = 0;

    virtual Color3 getDefusePart(const Vector3 &s, const Vector3 &m, const std::shared_ptr<LightSource> &lightSource,
                                 const std::shared_ptr<AbstractMaterial> &material) = 0;

    virtual Color3 getSpecularPart(const Vector3 &h, const Vector3 &s, const Vector3 &m, const Vector3 &v,
                                                        const std::shared_ptr<LightSource> &lightSource,
                                                        const std::shared_ptr<AbstractMaterial> &material) = 0;

};


#endif //RAYTRACINGENGINE_ABSTRACTSHADER_H
