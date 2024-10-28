//
// Created by berka on 08/10/2024.
//

#include "../include/Scene.h"
#include "Core/include/Ray.h"
#include "Geometry/include/HitInfo.h"
#include "Geometry/include/unitGeometricObjects/HitObject.h"
#include "iostream"

Color3 Scene::shade(Ray &ray) {
    Intersection best;
    getFirstHit(ray, best);

    if (best.numHits == 0){
        return {0, 0, 0};
    }

    std::vector<std::shared_ptr<LightSource>> lightsThatHitsObject;
    lightsThatHitsObject.reserve(listOfLightsSourcePointers.size());


    for(const auto& listOfLightsSourcePointer : listOfLightsSourcePointers){

        Eigen::Vector3d vector3 = listOfLightsSourcePointer->location.point.head(3) - best.getHits(0)->hitPoint.point.head(3);

        Vector3 s(vector3);

        Ray ObjectToLightRay(best.getHits(0)->hitPoint, s);

        Intersection checkShadow;

        getFirstHit(ObjectToLightRay, checkShadow);

        if (checkShadow.numHits != 0){
            lightsThatHitsObject.emplace_back(listOfLightsSourcePointer);
        }

        //lightsThatHitsObject.emplace_back(listOfLightsSourcePointer);
    }

    if (lightsThatHitsObject.empty()){
        return {0, 0, 0};
    }

    return shader->shade(ray, best, lightsThatHitsObject,  best.getHits(0)->hitObject->material);
}

void Scene::getFirstHit(Ray &ray, Intersection &best) {
    Intersection inter;
    best.numHits = 0;

    //for each objet in turn, ^pionted to by pObj

    for (auto &listOfObjectPointer: listOfObjectPointers) {

        if (!listOfObjectPointer->hit(ray, inter)) {
            continue;
        }
        if (best.numHits == 0 || inter.getHits(0)->hitTime < best.getHits(0)->hitTime) {
            best.set(inter);
        }
    }
}




Scene::Scene() {

}

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
