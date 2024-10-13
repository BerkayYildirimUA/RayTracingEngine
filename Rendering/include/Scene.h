//
// Created by berka on 08/10/2024.
//

#ifndef RAYTRACINGENGINE_SCENE_H
#define RAYTRACINGENGINE_SCENE_H
#include "Core/include/Color3.h"
#include "Math/include/Point3.h"
#include "Core/include/Ray.h"
#include "Geometry/include/Intersection.h"

class Scene {

public:
    Color3 shade(Ray &ray);

    void getFirstHit(Ray& ray, Intersection& best);
};


#endif //RAYTRACINGENGINE_SCENE_H
