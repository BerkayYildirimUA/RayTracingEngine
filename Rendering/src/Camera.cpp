//
// Created by berka on 07/10/2024.
//

#include "Rendering/include/Camera.h"
#include "Core/include/Color3.h"
#include "iostream"

void Camera::raytrace(Scene &scn, int blocksize) {
    Ray theRay;
    theRay.setStart(eye);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, nColumns, 0, nRows, -1, 1);
    glDisable(GL_LIGHTING);

    for (int row = 0; row <= nRows; row++) {
        for (int col = 0; col <= nRows; col++) {
            //theRay.setDir(); //TODO set dir
            Color3 clr = scn.shade(theRay);
            glColor3f(clr.R, clr.B, clr.B);
            glRecti(col, row, col + blocksize, row + blocksize);
        }
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);

    std::cout << width << ", " << height << std::endl;
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
            glfwCreateWindow(nColumns, nRows, "RayTracing", nullptr, nullptr),
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

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);


}

void Camera::initialize() {
    this->initializeOpenGL();

    if (window == nullptr) {
        return;
    }

    // rendering loop
    while (!glfwWindowShouldClose(window.get())) {

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // check and call events and swap the buffers
        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }

    glfwTerminate();
}

