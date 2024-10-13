//
// Created by berka on 07/10/2024.
//

#ifndef RAYTRACINGENGINE_CAMERA_H
#define RAYTRACINGENGINE_CAMERA_H

#include "Core/include/Ray.h"
#include "Scene.h"
#include "Math/include/Point3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Camera {

private:
    Point3 eye;
    int nColumns;
    int nRows;

public:
    void raytrace(Scene& scn, int blocksize);

};


#endif //RAYTRACINGENGINE_CAMERA_H
