//
// Created by berka on 08/10/2024.
//

#include "../include/Scene.h"
#include "Core/include/Ray.h"
#include "Geometry/include/HitInfo.h"
#include "Geometry/include/unitGeometricObjects/HitObject.h"
#include "iostream"
/*
Color3 Scene::shade(const Ray &ray) {
    Intersection best;
    getFirstHit(ray, best);

    if (best.numHits == 0) {
        return {0, 0, 0};
    }


    Eigen::Vector4d hitPoint = best.getHits(0)->hitObject->getTransform() * best.getHits(0)->hitPoint.point;

    Ray feeler;
    feeler.setStart(Point3(hitPoint - 0.001 * ray.dir.vector.normalized()));


    Color3 color = shader->getAmbientPart(listOfLightsSourcePointers[0], best.getHits(0)->hitObject->material);

    for (const auto &lightSource: listOfLightsSourcePointers) {

        Eigen::Vector4d lightPos = lightSource->location.point;

        feeler.setDir(Vector3( lightPos - hitPoint));


        if (this->isInShadow(feeler)){
            continue;
        }

        color = color + shader->shade(ray, best, lightSource, best.getHits(0)->hitObject->material);
    }

    return color;
}*/
/*
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
}*/


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
/*
bool Scene::isInShadow(const Ray &ray) {
    return std::any_of(listOfObjectPointers.cbegin(), listOfObjectPointers.cend(),
                       [&ray](const auto &pointer) { return pointer->hit(ray); });
}*/

const std::vector<std::shared_ptr<HitObject>> &Scene::getListOfObjectPointers() const {
    return listOfObjectPointers;
}

const std::vector<std::shared_ptr<LightSource>> &Scene::getListOfLightsSourcePointers() const {
    return listOfLightsSourcePointers;
}
