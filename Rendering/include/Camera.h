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
#include "iostream"

class Camera {

private:
    Point3 eye;
    Vector3 normalRightVector = {1, 0, 0}, normalUpVector = {0, 1, 0}, normalDistanceVector {0, 0, -1}; // u, v, n
    double viewAngle, aspectRatio;

    int screenWidth, screenHight;

    double distance;

    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window{nullptr, glfwDestroyWindow};

    void initializeOpenGL();


public:
    void raytrace(Scene &scn, int blockSize);

    void initialize(Scene &scn, Point3 &eye);

    const Point3 &getEye() const;

    Camera(int width, double aspectRatio, double viewAngle)
            : viewAngle(viewAngle), aspectRatio(aspectRatio), screenWidth(width) {

        screenHight = screenWidth/aspectRatio;
        distance = screenHight/tan(Transformations::degreeToRad(viewAngle) /2);

    }

    Camera(int width, int height, double viewAngle)
            : viewAngle(viewAngle), screenHight(height), screenWidth(width) {
        this->aspectRatio = static_cast<double>(width) / height;

        distance = screenHight / tan(Transformations::degreeToRad(viewAngle) /2);

    }

    void updateResolution(int newWidth, int newHeight) {
        this->aspectRatio = static_cast<double>(newWidth) / newHeight;
        screenHight = newHeight;
        screenWidth = newWidth;
        distance = screenHight / tan(Transformations::degreeToRad(viewAngle) /2);

    }

    void slide(double deltaDistance,double deltaRight, double deltaUp){
        eye.point.x() += deltaDistance * normalDistanceVector.vector.x() + deltaRight * normalRightVector.vector.x() + deltaUp * normalUpVector.vector.x();
        eye.point.y() += deltaDistance * normalDistanceVector.vector.y() + deltaRight * normalRightVector.vector.y() + deltaUp * normalUpVector.vector.y();
        eye.point.x() += deltaDistance * normalDistanceVector.vector.z() + deltaRight * normalRightVector.vector.z() + deltaUp * normalUpVector.vector.z();

    }

};


#endif //RAYTRACINGENGINE_CAMERA_H
