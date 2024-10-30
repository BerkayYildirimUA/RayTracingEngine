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

Color3
CookTorranceShading::shade(const Ray &ray, Intersection &best,
                           const std::vector<std::shared_ptr<LightSource>> &lightSources,
                           std::shared_ptr<AbstractMaterial> &material) {


    auto fresnelMaterial = std::dynamic_pointer_cast<FresnelMaterial>(material);
    if (!fresnelMaterial) {
        throw std::runtime_error("Failed to cast AbstractMaterial to FresnelMaterial");
    }

    Ray genRay;
    best.getHits(0)->hitObject->transformRayToObjectSpace(ray, genRay);


    Eigen::Vector3d vCords = -genRay.dir.vector.head(3);

    Vector3 v(vCords); //manual v calc trying idk
    Vector3 m(std::move(best.getHits(0)->hitNormal.vector));

    Point3 hitLocation = best.getHits(0)->hitPoint;


    v.vector.head(3).normalize();
    m.vector.head(3).normalize();

    double red = 0, green = 0, blue = 0;
    for (const auto &lightSource: lightSources) {
        Eigen::Vector3d sCords = (best.getHits(0)->hitObject->getInverseTransform() * lightSource->location.point).head(3) - hitLocation.point.head(3);
        Vector3 s(sCords);
        s.vector.head(3).normalize();

        Vector3 h = s + v;
        h.vector.head(3).normalize();

        red += calcIntensity(h, s, m, v, lightSource, fresnelMaterial, 0);;
        green += calcIntensity(h, s, m, v, lightSource, fresnelMaterial, 1);
        blue += calcIntensity(h, s, m, v, lightSource, fresnelMaterial, 2);

    }


    return {red, green, blue};
}

double
CookTorranceShading::calcIntensity(const Vector3 &h, const Vector3 &s, const Vector3 &m, const Vector3 &v,
                                   const std::shared_ptr<LightSource> &lightSource,
                                   const std::shared_ptr<FresnelMaterial> &material, int index) const {


    double ambientPart = lightSource->Iar.colors[index] * material->ambientLightFactor *
                         calcFresnelCoefficientForColor(0, material->getIndexOfRefractionByIndex(index));

    double defusePart = getDefusePart(s, m, lightSource, material, index);

    double specularPart = getSpecularPart(h, s, m, v, lightSource, material, index);

    return specularPart + ambientPart + defusePart;
}

double
CookTorranceShading::getDefusePart(const Vector3 &s, const Vector3 &m, const std::shared_ptr<LightSource> &lightSource,
                                   const std::shared_ptr<FresnelMaterial> &material, int index) const {


    double lambert = std::max(0.0, s.vector.head(3).dot(m.vector.head(3)));

    double secondPart = lightSource->Isr.colors[index] * dw * material->defusedLightFactor *
                        calcFresnelCoefficientForColor(0, material->getIndexOfRefractionByIndex(index)) * lambert;

    return secondPart;
}

double CookTorranceShading::getSpecularPart(const Vector3 &h, const Vector3 &s, const Vector3 &m, const Vector3 &v,
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

    double power = tan(theta) / material->roughness;
    power = -(power * power);

    double firstHalf =
            1 / (4 * material->roughness * material->roughness * cos(theta) * cos(theta) * cos(theta) * cos(theta));

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

    double c = cos(angleBetweenInRadians);
    double g = sqrt(indexOfRefraction * indexOfRefraction + c * c - 1);

    double gMinusC = g - c;
    double gPlusC = g + c;

    double firstTerm = (0.5 * (gMinusC * gMinusC)) / (gPlusC * gPlusC);
    double secondTerm = (c * gPlusC - 1) / (c * gMinusC + 1);
    secondTerm = 1 + secondTerm * secondTerm;

    if (std::isinf(secondTerm)){
        secondTerm = 1000000;
    }

    if (std::isinf(firstTerm)){
        firstTerm = 1000000;
    }

    return firstTerm * secondTerm;
}