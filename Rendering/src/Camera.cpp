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

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, nColumns, 0, nRows, -1, 1);
    glDisable(GL_LIGHTING);

    Vector3 u(1.0, 0.0, 0.0); // Right vector of the camera
    Vector3 v(0.0, 1.0, 0.0); // Up vector of the camera
    Vector3 Nn(0.0, 0.0, -5.0); // Forward (view direction) vector of the camera
    Vector3 dir;

    // Screen size (W and H)
    float W = this->nRows/2;  // Assuming normalized device coordinates range from -1 to 1
    float H = this->nColumns/2;

    for (int row = 0; row <= nRows; row++) {
        for (int col = 0; col <= nRows; col++) {

            float ndcX = (2.0f * col / nColumns) - 1.0f;
            float ndcY = (2.0f * row / nRows) - 1.0f;

            Eigen::Vector4d dir_vector = -Nn.vector + W * ndcX * u.vector + H * ndcY * v.vector;

            dir.vector(dir_vector);

            std::cout << dir_vector << "\n";

            theRay.setDir(std::move(dir));
            Color3 clr = scn.shade(theRay);
            glColor3f(clr.R, clr.B, clr.B);
            glRecti(col, row, col + blockSize, row + blockSize);
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

void Camera::initialize(Scene &scn, Point3& eye) {
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
        raytrace(scn, 10);
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

int Camera::getNColumns() const {
    return nColumns;
}

int Camera::getNRows() const {
    return nRows;
}

