//
// Created by berka on 08/10/2024.
//

#include "../include/Scene.h"
#include "Core/include/Ray.h"
#include "Geometry/include/HitInfo.h"
#include "Geometry/include/unitGeometricObjects/HitObject.h"
#include "iostream"

Color3 Scene::shade(const Ray &ray) {
    Intersection best;
    getFirstHit(ray, best);

    if (best.numHits == 0){
        return {0, 0, 0};
    }

    /*
    std::vector<std::shared_ptr<LightSource>> lightsThatHitsObject = makeShadowVector(best);

    if (lightsThatHitsObject.empty()){
        return {0, 0, 0 };
    }*/

    return shader->shade(ray, best, listOfLightsSourcePointers,  best.getHits(0)->hitObject->material);
}

std::vector<std::shared_ptr<LightSource>> Scene::makeShadowVector(Intersection &best) {
    std::vector<std::shared_ptr<LightSource>> lightsThatHitsObject;
    lightsThatHitsObject.reserve(listOfLightsSourcePointers.size());


    for(const auto& listOfLightsSourcePointer : listOfLightsSourcePointers){

        Eigen::Vector3d vectorToLight  = listOfLightsSourcePointer->location.point.head(3) - best.getHits(0)->hitPoint.point.head(3);

        Vector3 s(vectorToLight);

        Ray ObjectToLightRay(best.getHits(0)->hitPoint, s);

        Intersection checkShadow;

        getFirstHit(ObjectToLightRay, checkShadow);

        double distanceToLight = vectorToLight.norm();

        if (checkShadow.numHits != 0 && checkShadow.getHits(0)->hitTime < distanceToLight){
            lightsThatHitsObject.emplace_back(listOfLightsSourcePointer);
        }

        //lightsThatHitsObject.emplace_back(listOfLightsSourcePointer);
    }
    return lightsThatHitsObject;
}

void Scene::getFirstHit(const Ray &ray, Intersection &best) {
    Intersection inter;
    best.numHits = 0;

    for (auto &listOfObjectPointer: listOfObjectPointers) {

        if (!listOfObjectPointer->hit(ray, inter)) {
            continue;
        }
        if (best.numHits == 0 || inter.getHits(0)->hitTime < best.getHits(0)->hitTime) {
            best.set(inter);
        }
    }
}




Scene::Scene() = default;

void Scene::setObjects(const std::vector<std::shared_ptr<HitObject>> &vector) {
    this->listOfObjectPointers = vector;
}

void Scene::setListOfLightsSourcePointers(const std::vector<std::shared_ptr<LightSource>> &listOfLightsSourcePointers) {
    Scene::listOfLightsSourcePointers = listOfLightsSourcePointers;
}

void Scene::setShader(std::unique_ptr<AbstractShader> &&shader) {
    Scene::shader = std::move(shader);
}

Scene::Scene(const std::vector<std::shared_ptr<HitObject>> &listOfObjectPointers,
             const std::vector<std::shared_ptr<LightSource>> &listOfLightsSourcePointers,
             std::unique_ptr<AbstractShader> shader) : listOfObjectPointers(listOfObjectPointers),
                                                              listOfLightsSourcePointers(listOfLightsSourcePointers),
                                                              shader(std::move(shader)) {}
