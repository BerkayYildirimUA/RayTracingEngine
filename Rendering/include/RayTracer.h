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

    const int MAX_RECURSION_DEPTH = 15;

public:

    [[nodiscard]] const std::unique_ptr<AbstractShader> &getShader() const;



    void render(Scene &scn, Camera *camera, int blockSize);
    void getFirstHit(const Ray &ray, Intersection &best, Scene &scn);
    Color3 shade(const Ray &ray, Scene &scn);
    Color3 shade(const Ray &ray, Scene &scn, int recursionDepth);
    Color3 shade(const Ray &ray, Scene &scn, Intersection &best);
    bool isInShadow(const Ray &ray, Scene &scn);

    Color3
    noAntiAlsiasing(Scene &scn, const Camera *camera, int nColumns, int nRows, Ray &threadRay, Vector3 &dir,
                    const Vector3 &distanceVector, double row, double col);

    Color3
    antiAlsiasing(Scene &scn, const Camera *camera, int nColumns, int nRows, Ray &threadRay, Vector3 &dir,
                    const Vector3 &distanceVector, int row, int col);
};


#endif //RAYTRACINGENGINE_RAYTRACER_H
