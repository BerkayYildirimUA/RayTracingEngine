//
// Created by berka on 08/10/2024.
//

#include "../include/Scene.h"
#include "Core/include/Ray.h"
#include "Geometry/include/HitInfo.h"
#include "Geometry/include/unitGeometricObjects/HitObject.h"
#include "iostream"
#include "Geometry/include/unitGeometricObjects/PrimitiveObjects.h"

Scene::Scene() = default;

void Scene::setObjects(const std::vector<std::shared_ptr<HitObject>> &vector) {
    this->listOfObjectPointers = vector;
}

void Scene::setListOfLightsSourcePointers(const std::vector<std::shared_ptr<LightSource>> &listOfLightsSourcePointers) {
    Scene::listOfLightsSourcePointers = listOfLightsSourcePointers;
}


Scene::Scene(const std::vector<std::shared_ptr<HitObject>> &listOfObjectPointers,
             const std::vector<std::shared_ptr<LightSource>> &listOfLightsSourcePointers) : listOfObjectPointers(listOfObjectPointers),
                                                       listOfLightsSourcePointers(listOfLightsSourcePointers) {

    for (const auto &obj: listOfObjectPointers) {
        auto primitive = std::dynamic_pointer_cast<PrimitiveObjects>(obj);
        if (primitive) {
            auto material = primitive->getMaterial();
            if (material->emission != Color3{0, 0, 0}) {
                glowingObjects.push_back(primitive);
            }
            continue;
        }

        auto boolean = std::dynamic_pointer_cast<Boolean>(obj);
        if (boolean) {
            collectGlowingObjects(boolean->getLeft(), glowingObjects);
            collectGlowingObjects(boolean->getRight(), glowingObjects);
        }
    }

}

const std::vector<std::shared_ptr<HitObject>> &Scene::getListOfObjectPointers() const {
    return listOfObjectPointers;
}

const std::vector<std::shared_ptr<LightSource>> &Scene::getListOfLightsSourcePointers() const {
    return listOfLightsSourcePointers;
}

void Scene::loadScene(const std::string &filename) {

}

void Scene::collectGlowingObjects(const std::shared_ptr<HitObject>& obj,
                                  std::vector<std::shared_ptr<PrimitiveObjects>>& glowingObjects) {
    auto primitive = std::dynamic_pointer_cast<PrimitiveObjects>(obj);
    if (primitive) {
        auto material = primitive->getMaterial();
        if (material->emission != Color3{0, 0, 0}) {
            glowingObjects.push_back(primitive);
        }
        return;
    }

    auto boolean = std::dynamic_pointer_cast<Boolean>(obj);
    if (boolean) {
        collectGlowingObjects(boolean->getLeft(), glowingObjects);
        collectGlowingObjects(boolean->getRight(), glowingObjects);
    }
}

const std::vector<std::shared_ptr<PrimitiveObjects>> &Scene::getGlowingObjects() const {
    return glowingObjects;
}

