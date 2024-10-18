//
// Created by berka on 07/10/2024.
//

#include "Rendering/include/Camera.h"
#include "Core/include/Color3.h"
#include "iostream"
#include <chrono>
#include <thread>

void Camera::raytrace(Scene &scn, int blockSize) {
    Ray theRay;
    theRay.setStart(std::move(this->eye));

    int nColumns = screenWidth / blockSize;
    int nRows = screenHight / blockSize;


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, 0, screenHight, -1, 1);
    glDisable(GL_LIGHTING);

    Vector3 dir;

    // Screen size (W and H)

    Vector3 distanceVector(normalDistanceVector.vector * distance);

    for (int row = 0; row < (screenWidth/2); row++) {
        for (int col = 0; col < (screenHight/2); col++) {

            double rightVectorAmplitude = (screenWidth/2) * (2.0 * col / nColumns);
            double upVectorAmplitude = (screenHight/2) * (2.0*row / nRows);

            Eigen::Vector4d dir_vector = -distanceVector.vector + rightVectorAmplitude * normalRightVector.vector + upVectorAmplitude * normalUpVector.vector;

            dir.vector(dir_vector);

            theRay.setDir(std::move(dir));
            Color3 clr = scn.shade(theRay);
            glColor3f(clr.R, clr.B, clr.B);
            glRecti(col, row, col + blockSize, row + blockSize);
        }
    }
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    auto camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if (camera){
        camera->updateResolution(width, height);
    }

}

void Camera::initializeOpenGL() {

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    //openGL 3.3, using only core functions
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    glViewport(0, 0, screenWidth, screenHight);
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);


}

void Camera::initialize(Scene &scn, Point3& eye) {
    this->initializeOpenGL();

    this->eye = eye;

    if (window == nullptr) {
        return;
    }

    const int MAX_FPS = 30;
    const double FRAME_TIME = 1.0 / MAX_FPS;

    // rendering loop
    while (!glfwWindowShouldClose(window.get())) {

        auto frame_start = std::chrono::high_resolution_clock::now();


        //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // check and call events and swap the buffers
        raytrace(scn, 1);
        glfwSwapBuffers(window.get());
        glfwPollEvents();

        auto frame_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = frame_end - frame_start;

        // If the frame finished early, sleep for the remaining time
        if (elapsed.count() < FRAME_TIME) {
            std::this_thread::sleep_for(std::chrono::duration<double>(FRAME_TIME - elapsed.count()));
        }

    }

    glfwTerminate();
}

const Point3 &Camera::getEye() const {
    return eye;
}


