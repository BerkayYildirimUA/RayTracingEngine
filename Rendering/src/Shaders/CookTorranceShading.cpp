//
// Created by berka on 27/10/2024.
//

#include "Rendering/include/Shaders/CookTorranceShading.h"
#include "thread"
#include "Intersection.h"
#include "cmath"
#include <memory>

Color3
CookTorranceShading::shade(Ray &ray, Intersection &best, const std::vector<std::shared_ptr<LightSource>> &lightSources,
                           std::shared_ptr<AbstractMaterial> &material) {


    auto fresnelMaterial = std::dynamic_pointer_cast<FresnelMaterial>(material);
    if (!fresnelMaterial) {
        throw std::runtime_error("Failed to cast AbstractMaterial to FresnelMaterial");
    }

    Eigen::Vector3d vCords = -ray.dir.vector.head(3);
    Vector3 v(vCords);
    Vector3 m = best.getHits(0)->hitNormal;

    double m_magnitude = m.vector.head(3).norm();

    Point3 hitLocation = best.getHits(0)->hitPoint;

    double red = 0, green = 0, blue = 0;
    for (auto lightSource: lightSources) {
        Eigen::Vector3d sCords = lightSource->location.point.head(3) - hitLocation.point.head(3);
        Vector3 s(sCords);
        Vector3 h = s + v;


        //color3.colors[0] += calcIntensity(h, s, m, v, lightSource, m_magnitude, fresnelMaterial, 0);

        double redLocal = 0, greenLocal = 0, blueLocal = 0;


        std::thread redThread(
                [&]() { redLocal = calcIntensity(h, s, m, v, lightSource, m_magnitude, fresnelMaterial, 0); });
        std::thread greenThread(
                [&]() { greenLocal = calcIntensity(h, s, m, v, lightSource, m_magnitude, fresnelMaterial, 1); });
        std::thread blueThread(
                [&]() { blueLocal = calcIntensity(h, s, m, v, lightSource, m_magnitude, fresnelMaterial, 2); });


        redThread.join();
        greenThread.join();
        blueThread.join();

        red += redLocal;
        green += greenLocal;
        blue += blueLocal;

    }


    return {red, green, blue};
}

double
CookTorranceShading::calcIntensity(Vector3 &h, Vector3 &s, Vector3 &m, Vector3 &v, const std::shared_ptr<LightSource>& lightSource, double m_magnitude, std::shared_ptr<FresnelMaterial> &material, int index) {


    double firstPart = lightSource->Iar.colors[index] * material->ambientLightFactor *
                       calcFresnelCoefficientForColor(0, material->getIndexOfRefractionByIndex(index));

    double secondPart = getSecondPart(s, m, lightSource, m_magnitude, material, index);

    double thirdPart = getThirdPart(h, s, m, v, lightSource, material, index);

    return firstPart + secondPart + thirdPart;
}

double
CookTorranceShading::getSecondPart(const Vector3 &s, const Vector3 &m, const std::shared_ptr<LightSource> &lightSource,
                                   double m_magnitude, const std::shared_ptr<FresnelMaterial> &material, int index) {

    double s_magnitude = s.vector.head(3).norm();

    double lambert = std::max(0.0, s.vector.head(3).dot(m.vector.head(3)) / (s_magnitude * m_magnitude));

    double secondPart = lightSource->Isr.colors[index] * dw * material->defusedLightFactor *
                        calcFresnelCoefficientForColor(0, material->getIndexOfRefractionByIndex(index)) * lambert;
    return secondPart;
}

double CookTorranceShading::getThirdPart(Vector3 &h, const Vector3 &s, Vector3 &m, const Vector3 &v,
                                         const std::shared_ptr<LightSource> &lightSource,
                                         const std::shared_ptr<FresnelMaterial> &material, int index) {

    double G;
    getG(s, v, h, m, G);
    double D = getD(h, m, material);
    double spec =
            calcFresnelCoefficientForColor(s.angleBetweenInRadians(m), material->getIndexOfRefractionByIndex(index)) * D * G;
    spec = spec / (m * v);
    return lightSource->Isr.colors[index] * dw * material->specularLightFactor * spec;
}

void CookTorranceShading::getG(const Vector3 &s, const Vector3 &v, Vector3 &h, Vector3 &m, double &G) const {
    double gCommonPart = (2 * (m * h)) / (h * s);
    double Gm = gCommonPart * (m * s);
    double Gs = gCommonPart * (m * v);
    G = std::min(Gs, std::min(Gm, 1.0));
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

double CookTorranceShading::calcFresnelCoefficientForColor(double angleBetweenInRadians, double indexOfRefraction) {
    if (angleBetweenInRadians == 0) {
        double up = indexOfRefraction - 1.0;
        double down = indexOfRefraction + 1.0;
        return (up * up) / (down * down);
    }

    double c = cos(angleBetweenInRadians);
    double g = sqrt(indexOfRefraction * indexOfRefraction + c * c - 1);

    double gMinusC = g - c;
    double gPlusC = g + c;

    double firstTerm = 0.5 * (gMinusC * gMinusC) / (gPlusC * gPlusC);
    double secondTerm = (c * gPlusC - 1) / (c * gMinusC + 1);
    secondTerm = 1 + secondTerm * secondTerm;

    return firstTerm * secondTerm;
}