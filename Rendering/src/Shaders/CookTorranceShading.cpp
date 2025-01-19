//
// Created by berka on 27/10/2024.
//

#include "Rendering/include/Shaders/CookTorranceShading.h"
#include "thread"
#include "Intersection.h"
#include "cmath"
#include <memory>
#include "Geometry/include/unitGeometricObjects/HitObject.h"
#include "iostream"
#include "Geometry/include/unitGeometricObjects/UnitSphere.h"
#include "DebugFlags.h"
#include "Intersection.h"
#include "HitInfo.h"

Color3
CookTorranceShading::shade(const Ray &ray, const Intersection &best,
                           const std::shared_ptr<LightSource> &lightSource) {

    auto material = best.getHit(0)->hitObject->material;

    auto fresnelMaterial = std::dynamic_pointer_cast<FresnelMaterial>(material);
    if (!fresnelMaterial) {
        throw std::runtime_error("Failed to cast AbstractMaterial to FresnelMaterial");
    }

    Ray genRay;
    best.getHit(0)->hitObject->transformRayToObjectSpace(ray, genRay); //object space

    Vector3 v(-genRay.dir.vector.head(3)); //object space
    v.normalize();

    Vector3 m(best.getHit(0)->hitNormal); //object space
    m.normalize();


    Point3 hitLocation = best.getHit(0)->hitPoint;
    Vector3 s((best.getHit(0)->hitObject->getInverseTransform() * lightSource->location.point).head(3) - hitLocation.point.head(3));
    s.normalize();

    Vector3 h = s + v;
    h.normalize();

    Color3 texture = fresnelMaterial->getTexture(hitLocation);



    auto calcDefuseAndSpecular = [&](int index) -> double {
        double defusePart = 0;
        double specularPart = 0;

        if (!DebugFlags::getTurnOffDefusedColors()) {
            defusePart = getDefusePartOneColor(s, m, lightSource, fresnelMaterial, index) * texture.getColor(index);
        }

        if (!DebugFlags::getTurnOffSpecularColors()) {
            specularPart = getSpecularPartOneColor(h, s, m, v, lightSource, fresnelMaterial, index);
        }

        return specularPart + defusePart;
    };

    double red = 0, green = 0, blue = 0;
    red += calcDefuseAndSpecular( 0);;
    green += calcDefuseAndSpecular(1);
    blue += calcDefuseAndSpecular(2);


    return {red, green, blue};
}

double CookTorranceShading::getAmbientPartOneColor(const std::shared_ptr<LightSource> &lightSource,
                                                   const Intersection &best, int index) const {
    auto material = best.getHit(0)->hitObject->material;

    auto fresnelMaterial = std::dynamic_pointer_cast<FresnelMaterial>(material);
    if (!fresnelMaterial) {
        throw std::runtime_error("Failed to cast AbstractMaterial to FresnelMaterial");
    }

    double ambientPart = lightSource->Iar.colors[index] * fresnelMaterial->ambientLightFactor *
                         calcFresnelCoefficientForColor(0, fresnelMaterial->getIndexOfRefractionByIndex(index));

    Point3 hitLocation = best.getHit(0)->hitPoint;
    auto texture = fresnelMaterial->getTexture(hitLocation);

    return ambientPart * texture.getColor(index);
}

double
CookTorranceShading::getDefusePartOneColor(const Vector3 &s, const Vector3 &m,
                                           const std::shared_ptr<LightSource> &lightSource,
                                           const std::shared_ptr<FresnelMaterial> &material, int index) const {


    double lambert = std::max(0.0, s * m );

    double secondPart = lightSource->Isr.colors[index] * dw * material->defusedLightFactor *
                        calcFresnelCoefficientForColor(0, material->getIndexOfRefractionByIndex(index)) * lambert;

    return secondPart;
}

double
CookTorranceShading::getSpecularPartOneColor(const Vector3 &h, const Vector3 &s, const Vector3 &m, const Vector3 &v,
                                             const std::shared_ptr<LightSource> &lightSource,
                                             const std::shared_ptr<FresnelMaterial> &material, int index) const {

    double G = getG(s, v, h, m);

    double D = getD(h, m, material);

    double spec =
            calcFresnelCoefficientForColor(s.angleBetweenInRadians(m), material->getIndexOfRefractionByIndex(index)) *
            D * G;
    spec = spec / (m * v);
    return lightSource->Isr.colors[index] * dw * material->specularLightFactor * spec;
}

double CookTorranceShading::getG(const Vector3 &s, const Vector3 &v, const Vector3 &h, const Vector3 &m) const {
    double hS = (h*s);

    if (hS == 0){
        hS = 1e-16;
    }

    double gCommonPart = (2 * (m * h)) / hS;
    double Gm = gCommonPart * (m * s);
    double Gs = gCommonPart * (m * v);
    return std::min(Gs, std::min(Gm, 1.0));
}

double
CookTorranceShading::getD(const Vector3 &h, const Vector3 &m, const std::shared_ptr<FresnelMaterial> &material) const {
    double theta = m.angleBetweenInRadians(h);

    double roughness = std::max(material->roughness, 0.000001);

    double power = tan(theta) / roughness;
    power = -(power * power);

    double cosTheta = GeometricFunctionsLookup::getCos(theta);

    double firstHalf =
            1 / (4 * roughness * roughness * cosTheta * cosTheta * cosTheta * cosTheta);

    double D = firstHalf * exp(power);
    return D;
}

double
CookTorranceShading::calcFresnelCoefficientForColor(double angleBetweenInRadians, double indexOfRefraction) const {
    if (angleBetweenInRadians == 0) {
        double up = indexOfRefraction - 1.0;
        double down = indexOfRefraction + 1.0;
        return (up * up) / (down * down);
    }

    double c = GeometricFunctionsLookup::getCos(angleBetweenInRadians);
    double g = sqrt(indexOfRefraction * indexOfRefraction + c * c - 1);

    double gMinusC = g - c;
    double gPlusC = g + c;

    double firstTerm = (0.5 * (gMinusC * gMinusC)) / (gPlusC * gPlusC);
    double secondTerm = (c * gPlusC - 1) / (c * gMinusC + 1);
    secondTerm = 1 + secondTerm * secondTerm;

    if (std::isinf(secondTerm)) {
        secondTerm = 1000000;
    }

    if (std::isinf(firstTerm)) {
        firstTerm = 1000000;
    }

    return firstTerm * secondTerm;
}

Color3 CookTorranceShading::getAmbientPart(const std::shared_ptr<LightSource> &lightSource,
                                           const Intersection &best) {

    return {getAmbientPartOneColor(lightSource, best, 0),
            getAmbientPartOneColor(lightSource, best, 1),
            getAmbientPartOneColor(lightSource, best, 2)};
}

Color3
CookTorranceShading::getDefusePart(const Vector3 &s, const Vector3 &m, const std::shared_ptr<LightSource> &lightSource,
                                   const std::shared_ptr<AbstractMaterial> &material) {
    auto fresnelMaterial = std::dynamic_pointer_cast<FresnelMaterial>(material);
    if (!fresnelMaterial) {
        throw std::runtime_error("Failed to cast AbstractMaterial to FresnelMaterial");
    }

    return {getDefusePartOneColor(s, m, lightSource, fresnelMaterial, 0),
            getDefusePartOneColor(s, m, lightSource, fresnelMaterial, 1),
            getDefusePartOneColor(s, m, lightSource, fresnelMaterial, 2)};
}

Color3 CookTorranceShading::getSpecularPart(const Vector3 &h, const Vector3 &s, const Vector3 &m, const Vector3 &v,
                                            const std::shared_ptr<LightSource> &lightSource,
                                            const std::shared_ptr<AbstractMaterial> &material) {

    auto fresnelMaterial = std::dynamic_pointer_cast<FresnelMaterial>(material);
    if (!fresnelMaterial) {
        throw std::runtime_error("Failed to cast AbstractMaterial to FresnelMaterial");
    }

    return {getSpecularPartOneColor(h, s, m, v, lightSource, fresnelMaterial, 0),
            getSpecularPartOneColor(h, s, m, v, lightSource, fresnelMaterial, 1),
            getSpecularPartOneColor(h, s, m, v, lightSource, fresnelMaterial, 2)};
}
