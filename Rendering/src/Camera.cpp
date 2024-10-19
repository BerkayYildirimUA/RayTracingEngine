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
    glDisable(GL_DEPTH_TEST);


    Vector3 dir;

    // Screen size (W and H)

    Vector3 distanceVector(normalDistanceVector.vector * distance);

    //Eigen::MatrixXd redChannel(nColumns, nRows);


    for (int row = 0; row < nRows; row++) {
        bool loggedFirstRedCol = false;

        for (int col = 0; col < nColumns; col++) {

            double rightVectorAmplitude = (screenWidth / 2.0) * ((2.0 * col / nColumns) - 1);
            double upVectorAmplitude = (screenHight / 2.0) * ((2.0 * row / nRows) - 1);

            Eigen::Vector4d dir_vector = -distanceVector.vector + rightVectorAmplitude * normalRightVector.vector +
                                         upVectorAmplitude * normalUpVector.vector;

            dir_vector.normalize();
            dir.vector = std::move(dir_vector);

            theRay.setDir(std::move(dir));
            Color3 clr = scn.shade(theRay);

            int flippedRow = nRows - row - 1;

            /*
            if (row % 50 == 0 || col % 50 == 0) {
                glColor3f(0, 255, 0);
            } */

            glColor3f(clr.R, clr.G, clr.B);

            glRecti(col * blockSize, flippedRow * blockSize, (col + 1) * blockSize, (flippedRow + 1) * blockSize);

        }
    }

    /*std::ofstream file("color_matrix.txt");

    if (file.is_open()) {
        // Write the red channel matrix
        file << "Red Channel:\n" << redChannel << "\n";
        file.close();

        // Verify if the file was written successfully
        std::string filePath = std::filesystem::absolute("color_matrix.txt").string();
        if (std::filesystem::exists(filePath)) {
            std::cout << "File successfully written to: " << filePath << std::endl;
        } else {
            std::cerr << "Error: File was not created in the expected location." << std::endl;
        }
    } else {
        std::cerr << "Error: Unable to create or write to 'color_matrix.txt'.\n";
    }*/

}


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
            camera->slide(0, 0, -0.1);
        } else if (key == GLFW_KEY_DOWN) {
            camera->slide(0, 0, 0.1);
        } else if (key == GLFW_KEY_LEFT) {
            camera->slide(0, -0.1, 0);
        } else if (key == GLFW_KEY_RIGHT) {
            camera->slide(0, 0.1, 0);
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

    const int MAX_FPS = 60;
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


