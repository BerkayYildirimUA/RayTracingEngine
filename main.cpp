#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Math/include/Transformations.h"
#include "Rendering/include/Camera.h"
#include "Geometry/include/unitGeometricObjects/creation/ObjectFactory.h"
#include "Geometry/include/unitGeometricObjects/UnitCircle.h"


/*
 * using the following book for the installation of OpenGl.
 * "Joey De Vries, Learn OpenGL: Learn modern OpenGL graphics programming in a step-by-step fashion. Kendall & Welling, 2020."
 *
 * 217-218
 */


int main() {

    Camera camera(1000, 1000);

    Scene scene;

    std::vector<std::shared_ptr<HitObject>> vector;
    vector.reserve(1);


    vector.emplace_back(ObjectFactory::createObject<UnitCircle>());

    scene.setObjects(vector);

    Point3 point(-3, 0, 0);

    camera.initialize(scene, point);

    return 0;
}

