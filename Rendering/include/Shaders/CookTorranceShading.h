//
// Created by berka on 27/10/2024.
//

#ifndef RAYTRACINGENGINE_COOKTORRANCESHADING_H
#define RAYTRACINGENGINE_COOKTORRANCESHADING_H

#include "AbstractShader.h"
#include "Material/FresnelMaterial.h"

class CookTorranceShading : public AbstractShader {

public:
    Color3 shade(const Ray &ray, Intersection &best, const std::shared_ptr<LightSource> &lightSources,
                 std::shared_ptr<AbstractMaterial> &material) override;

    Color3 getAmbientPart(const std::shared_ptr<LightSource> &lightSource,
                          const std::shared_ptr<AbstractMaterial> &material) override;

    Color3 getDefusePart(const Vector3 &s, const Vector3 &m, const std::shared_ptr<LightSource> &lightSource,
                         const std::shared_ptr<AbstractMaterial> &material) override;

    Color3 getSpecularPart(const Vector3 &h, const Vector3 &s, const Vector3 &m, const Vector3 &v,
                           const std::shared_ptr<LightSource> &lightSource,
                           const std::shared_ptr<AbstractMaterial> &material) override;

private:
    const double dw = 0.0001;


    double calcDefuseAndSpecular(const Vector3 &h, const Vector3 &s, const Vector3 &m, const Vector3 &v,
                                 const std::shared_ptr<LightSource> &lightSource,
                                 const std::shared_ptr<FresnelMaterial> &material, int index) const;

    //Eigen::Vector3d calcFresnelCoefficient(double angleBetweenInRadians, std::unique_ptr<FresnelMaterial> &material);
    double calcFresnelCoefficientForColor(double angleBetweenInRadians, double indexOfRefraction) const;

    double getD(const Vector3 &h, const Vector3 &m, const std::shared_ptr<FresnelMaterial> &material) const;

    double getG(const Vector3 &s, const Vector3 &v, const Vector3 &h, const Vector3 &m) const;

    double getSpecularPartOneColor(const Vector3 &h, const Vector3 &s, const Vector3 &m, const Vector3 &v,
                                   const std::shared_ptr<LightSource> &lightSource,
                                   const std::shared_ptr<FresnelMaterial> &material, int index) const;

    double
    getDefusePartOneColor(const Vector3 &s, const Vector3 &m, const std::shared_ptr<LightSource> &lightSource,
                          const std::shared_ptr<FresnelMaterial> &material, int index) const;

    double
    getAmbientPartOneColor(const std::shared_ptr<LightSource> &lightSource, const std::shared_ptr<FresnelMaterial> &material,
                           int index) const;
};


#endif //RAYTRACINGENGINE_COOKTORRANCESHADING_H
