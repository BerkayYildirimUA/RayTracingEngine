//
// Created by berka on 02/11/2024.
//

#ifndef RAYTRACINGENGINE_RAYTRACER_H
#define RAYTRACINGENGINE_RAYTRACER_H

#include "Scene.h"
#include "Camera.h"
#include "Rendering/include/Shaders/CookTorranceShading.h"

class RayTracer {
private:
    std::unique_ptr<AbstractShader> shader = std::make_unique<CookTorranceShading>();

public:

    [[nodiscard]] const std::unique_ptr<AbstractShader> &getShader() const;

    void render(Scene &scn, Camera *camera, int blockSize);
    void getFirstHit(const Ray &ray, Intersection &best, Scene &scn);
    Color3 shade(const Ray &ray, Scene &scn);
    bool isInShadow(const Ray &ray, Scene &scn);
};


#endif //RAYTRACINGENGINE_RAYTRACER_H
