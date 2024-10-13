#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Math/include/Transformations.h"

/*
 * using the following book for the installation of OpenGl.
 * "Joey De Vries, Learn OpenGL: Learn modern OpenGL graphics programming in a step-by-step fashion. Kendall & Welling, 2020."
 *
 * 217-218
 */


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);

    std::cout << width << ", " << height << std::endl;
}

GLFWwindow* initializeOpenGL() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    //openGL 3.3, using only core functions
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return nullptr;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}


int main() {
    GLFWwindow* window = initializeOpenGL();
    if (window == nullptr) {
        return -1;
    }

    // rendering loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

