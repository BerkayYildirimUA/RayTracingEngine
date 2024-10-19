//
// Created by berka on 08/10/2024.
//

#include "../include/Scene.h"
#include "Core/include/Ray.h"
#include "Geometry/include/HitInfo.h"
#include "Geometry/include/unitGeometricObjects/HitObject.h"
#include "Geometry/include/RandomTesting/BlackHole.h"
#include "iostream"

Color3 Scene::shade(Ray &ray) {

    Color3 color;
    Intersection best;

    Color3 background(0, 0, 0);

    getFirstHit(ray, best);
    if (best.numHits == 0) {
        return background;
    }

    color.set(255, 0, 0);

//color.set(emissive color of object)//
    //  color.add(ambient, diffuse, and specular componets);
    //color.add(reflected and refracted componets);



    return color;
}


void getFirstHitRecur(Ray &ray, Intersection &best, int dept, std::vector<std::shared_ptr<HitObject>> &listOfObjectPointers) {
    Intersection inter;
    best.numHits = 0;
    dept++;

    if (dept >= 10){
        return;
    }

    //for each objet in turn, ^pionted to by pObj

    for (auto & listOfObjectPointer : listOfObjectPointers){

        if(!listOfObjectPointer->hit(ray, inter)){
            continue;
        }
        if (best.numHits == 0 || inter.getHits(0)->hitTime < best.getHits(0)->hitTime){
            best.set(inter);
        }


        for (auto &secRay : inter.secondaryRays) {
            getFirstHitRecur(secRay, inter, dept, listOfObjectPointers);
        }
    }
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

        for (auto &secRay: inter.secondaryRays) {
            //getFirstHit(secRay, inter);
            getFirstHitRecur(secRay, inter, 0, listOfObjectPointers);
        }
    }
}


Scene::Scene(const std::vector<std::shared_ptr<HitObject>> &vector) : listOfObjectPointers(
        vector) {
}

Scene::Scene() {

}

void Scene::setObjects(const std::vector<std::shared_ptr<HitObject>> &vector) {
    this->listOfObjectPointers = vector;
}
