//
// Created by berka on 08/10/2024.
//

#include "../include/Scene.h"
#include "Core/include/Ray.h"
#include "Geometry/include/HitInfo.h"
#include "Geometry/include/unitGeometricObjects/HitObject.h"
#include "iostream"

Scene::Scene() = default;

void Scene::setObjects(const std::vector<std::shared_ptr<HitObject>> &vector) {
    this->listOfObjectPointers = vector;
}

void Scene::setListOfLightsSourcePointers(const std::vector<std::shared_ptr<LightSource>> &listOfLightsSourcePointers) {
    Scene::listOfLightsSourcePointers = listOfLightsSourcePointers;
}


Scene::Scene(const std::vector<std::shared_ptr<HitObject>> &listOfObjectPointers,
             const std::vector<std::shared_ptr<LightSource>> &listOfLightsSourcePointers) : listOfObjectPointers(listOfObjectPointers),
                                                       listOfLightsSourcePointers(listOfLightsSourcePointers) {}

const std::vector<std::shared_ptr<HitObject>> &Scene::getListOfObjectPointers() const {
    return listOfObjectPointers;
}

const std::vector<std::shared_ptr<LightSource>> &Scene::getListOfLightsSourcePointers() const {
    return listOfLightsSourcePointers;
}

void Scene::loadScene(const std::string &filename) {

}
