//
// Created by berka on 07/10/2024.
//

#include "Rendering/include/Camera.h"
#include "Core/include/Color3.h"
#include "iostream"
#include <chrono>
#include <thread>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip> // for std::setw and std::setprecision
#include <future>
#include "RayTracer.h"
#include <numeric>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    auto camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));

    if (camera) {
        camera->updateResolution(width, height);
    }

}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    auto camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_UP) {
            camera->slide(0, 0, 1);
        } else if (key == GLFW_KEY_DOWN) {
            camera->slide(0, 0, -1);
        } else if (key == GLFW_KEY_LEFT) {
            camera->slide(0, -1, 0);
        } else if (key == GLFW_KEY_RIGHT) {
            camera->slide(0, 1, 0);
        } else if (key == GLFW_KEY_W) {
            camera->pitch(10);
        } else if (key == GLFW_KEY_S) {
            camera->pitch(-10);
        } else if (key == GLFW_KEY_A) {
            camera->yaw(10);
        } else if (key == GLFW_KEY_D) {
            camera->yaw(-10);
        } else if (key == GLFW_KEY_Q) {
            camera->roll(-10);
        } else if (key == GLFW_KEY_E) {
            camera->roll(10);
        } else if (key == GLFW_KEY_KP_SUBTRACT) {
            camera->slide(1, 0, 0);
        } else if (key == GLFW_KEY_KP_ADD) {
            camera->slide(-1, 0, 0);
        } else if (key == GLFW_KEY_ENTER) {
            std::cout << "cords are: (" << camera->getEye().point.x() << "," << camera->getEye().point.y() <<  "," << camera->getEye().point.z() << ") \n";
            std::cout << "normal Up is: (" << camera->getNormalUpVector().getX() << "," << camera->getNormalUpVector().getY() <<  "," << camera->getNormalUpVector().getZ() << ") \n";
            std::cout << "normal Right is: (" << camera->getNormalRightVector().getX() << "," << camera->getNormalRightVector().getY() <<  "," << camera->getNormalRightVector().getZ() << ") \n";
            std::cout << "normal Distance is: (" << camera->getNormalDistanceVector().getX() << "," << camera->getNormalDistanceVector().getY() <<  "," << camera->getNormalDistanceVector().getZ() << ") \n" << std::endl;

        }
    }
}

void Camera::initializeOpenGL() {

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    //openGL 3.3, need GLFW_OPENGL_COMPAT_PROFILE for glColor3f to work
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    window = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>(
            glfwCreateWindow(screenWidth, screenHight, "RayTracing", nullptr, nullptr),
            glfwDestroyWindow
    );


    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window.get());

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window.get());
        glfwTerminate();
        return;
    }

    glfwSetWindowUserPointer(window.get(), this);

    glfwGetFramebufferSize(window.get(), &screenWidth, &screenHight);
    glViewport(0, 0, screenWidth, screenHight);
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);
    glfwSetKeyCallback(window.get(), keyCallback);


}

void Camera::initialize(Scene &scn, Point3 &eye) {
    this->initializeOpenGL();
    this->eye = eye;

    if (window == nullptr) {
        return;
    }

    RayTracer rayTracer;

    int totalFrames = 0;

    std::vector<double> frameTimes;
    auto startTime = std::chrono::high_resolution_clock::now();


    while (!glfwWindowShouldClose(window.get())) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        glClear(GL_COLOR_BUFFER_BIT);

        rayTracer.render(scn, this, 1);

        glfwSwapBuffers(window.get());
        glfwPollEvents();

        auto frameEnd = std::chrono::high_resolution_clock::now();
        double frameTime = std::chrono::duration<double, std::milli>(frameEnd - frameStart).count();
        frameTimes.push_back(frameTime);
        totalFrames++;

    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double totalTime = std::chrono::duration<double>(endTime - startTime).count();

    // Calculate performance metrics
    std::sort(frameTimes.begin(), frameTimes.end());
    double avgFrameTime = std::accumulate(frameTimes.begin(), frameTimes.end(), 0.0) / frameTimes.size();
    double fps = 1000.0 / avgFrameTime;
    double low1PercentTime = frameTimes[frameTimes.size() * 0.01];
    double high99PercentTime = frameTimes[frameTimes.size() * 0.99];

    std::cout << "Performance Metrics:\n";
    std::cout << "Average FPS: " << fps << '\n';
    std::cout << "1% Low FPS: " << 1000.0 / low1PercentTime << '\n';
    std::cout << "99% High FPS: " << 1000.0 / high99PercentTime << '\n';
    std::cout << "Total Frames Generated: " << totalFrames << '\n';
    std::cout << "Total Runtime (seconds): " << totalTime << '\n';


    glfwTerminate();
}

const Point3 &Camera::getEye() const {
    return eye;
}

int Camera::getScreenHight() const {
    return screenHight;
}

int Camera::getScreenWidth() const {
    return screenWidth;
}

double Camera::getAspectRatio() const {
    return aspectRatio;
}

double Camera::getViewAngle() const {
    return viewAngle;
}

double Camera::getDistance() const {
    return distance;
}

const std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> &Camera::getWindow() const {
    return window;
}

const Vector3 &Camera::getNormalDistanceVector() const {
    return normalDistanceVector;
}

const Vector3 &Camera::getNormalUpVector() const {
    return normalUpVector;
}

const Vector3 &Camera::getNormalRightVector() const {
    return normalRightVector;
}

void Camera::setNormalRightVector(const Vector3 &normalRightVector) {
    Camera::normalRightVector = normalRightVector;
}

void Camera::setNormalUpVector(const Vector3 &normalUpVector) {
    Camera::normalUpVector = normalUpVector;
}

void Camera::setNormalDistanceVector(const Vector3 &normalDistanceVector) {
    Camera::normalDistanceVector = normalDistanceVector;
}


