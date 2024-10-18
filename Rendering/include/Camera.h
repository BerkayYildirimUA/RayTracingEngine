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
#include "memory"

class Camera {

private:
    Point3 eye;
    int nColumns;
    int nRows;
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window{nullptr, glfwDestroyWindow};

    void initializeOpenGL();

public:
    void raytrace(Scene &scn, int blockSize);

    void initialize(Scene &scn, Point3 &eye);

    const Point3 &getEye() const;

    int getNColumns() const;

    int getNRows() const;

    Camera(int nRows, int nColumns) {
        this->nRows = nRows;
        this->nColumns = nColumns;
    }


};


#endif //RAYTRACINGENGINE_CAMERA_H
