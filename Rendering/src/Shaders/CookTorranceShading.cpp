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
#include "Geometry/include/unitGeometricObjects/UnitCircle.h"

Color3
CookTorranceShading::shade(const Ray &ray, Intersection &best,
                           const std::shared_ptr<LightSource> &lightSource,
                           std::shared_ptr<AbstractMaterial> &material) {


    auto fresnelMaterial = std::dynamic_pointer_cast<FresnelMaterial>(material);
    if (!fresnelMaterial) {
        throw std::runtime_error("Failed to cast AbstractMaterial to FresnelMaterial");
    }

    Ray genRay;
    best.getHits(0)->hitObject->transformRayToObjectSpace(ray, genRay); //object space



   /* if (dynamic_cast<UnitSphere*>(best.getHits(0)->hitObject.get())){
        auto p = best.getHits(0)->hitObject->getTransform() * best.getHits(0)->hitPoint.point;
        if (p.z() > 11){
            if (p.y() > 0.98 && p.y() < 1.01) {
                if (p.x() > 0.78 && p.x() < 0.8) {
                    std::cout << best.getHits(0)->hitObject->getTransform() * best.getHits(0)->hitPoint.point << std::endl;
                }
            }
        }
    }*/

    Eigen::Vector3d vCords = -genRay.dir.vector.head(3);
    Vector3 v(vCords); //object space

    Vector3 m;
    m.set(best.getHits(0)->hitNormal); //object space


    Point3 hitLocation = best.getHits(0)->hitPoint;


    v.vector.head(3).normalize();
    m.vector.head(3).normalize();

    double red = 0, green = 0, blue = 0;
    Eigen::Vector3d sCords = (best.getHits(0)->hitObject->getInverseTransform() * lightSource->location.point).head(3) -
                             hitLocation.point.head(3);
    Vector3 s(sCords);
    s.vector.head(3).normalize();

    Vector3 h = s + v;
    h.vector.head(3).normalize();

    red += calcDefuseAndSpecular(h, s, m, v, lightSource, fresnelMaterial, 0);;
    green += calcDefuseAndSpecular(h, s, m, v, lightSource, fresnelMaterial, 1);
    blue += calcDefuseAndSpecular(h, s, m, v, lightSource, fresnelMaterial, 2);


    return {red, green, blue};
}

double
CookTorranceShading::calcDefuseAndSpecular(const Vector3 &h, const Vector3 &s, const Vector3 &m, const Vector3 &v,
                                           const std::shared_ptr<LightSource> &lightSource,
                                           const std::shared_ptr<FresnelMaterial> &material, int index) const {


    double defusePart = getDefusePartOneColor(s, m, lightSource, material, index);

    double specularPart = getSpecularPartOneColor(h, s, m, v, lightSource, material, index);

    return specularPart + defusePart;
}

double CookTorranceShading::getAmbientPartOneColor(const std::shared_ptr<LightSource> &lightSource,
                                                   const std::shared_ptr<FresnelMaterial> &material, int index) const {
    double ambientPart = lightSource->Iar.colors[index] * material->ambientLightFactor *
                         calcFresnelCoefficientForColor(0, material->getIndexOfRefractionByIndex(index));
    return ambientPart;
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
    double gCommonPart = (2 * (m * h)) / (h * s);
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
                                           const std::shared_ptr<AbstractMaterial> &material) {
    auto fresnelMaterial = std::dynamic_pointer_cast<FresnelMaterial>(material);
    if (!fresnelMaterial) {
        throw std::runtime_error("Failed to cast AbstractMaterial to FresnelMaterial");
    }
    return {getAmbientPartOneColor(lightSource, fresnelMaterial, 0),
            getAmbientPartOneColor(lightSource, fresnelMaterial, 1),
            getAmbientPartOneColor(lightSource, fresnelMaterial, 2)};
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
