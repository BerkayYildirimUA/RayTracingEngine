#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Math/include/Transformations.h"
#include "Rendering/include/Camera.h"
#include "Geometry/include/unitGeometricObjects/ObjectFactory.h"
#include "Geometry/include/unitGeometricObjects/UnitCircle.h"
#include "Geometry/include/unitGeometricObjects/UnitCube.h"
#include "Geometry/include/RandomTesting/BlackHole.h"




/*
 * using the following book for the installation of OpenGl.
 * "Joey De Vries, Learn OpenGL: Learn modern OpenGL graphics programming in a step-by-step fashion. Kendall & Welling, 2020."
 *
 * 217-218
 */


int main() {

    Scene scene;

    TransformationManager manager;
    manager.pushTranslation(-3, 0, 0);

    std::vector<std::shared_ptr<HitObject>> vector;
    vector.reserve(5);
    vector.emplace_back(ObjectFactory::createObject<UnitCircle>());
    vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager));

    manager.pushTranslation(3, 0, 0);
    manager.pushRotatePointZ(45);

    vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager));

    manager.pushScale(2, 1, 1);
    manager.pushTranslation(2, 2, -5);

    vector.emplace_back(ObjectFactory::createObject<UnitCircle>(manager));


    manager.pushTranslation(0, 0, -3);
    vector.emplace_back(ObjectFactory::createObject<BlackHole>(manager));

    Point3 point(0, 0, -50);
    Camera camera(1000, 1000, 60);
    scene.setObjects(vector);

    camera.initialize(scene, point);

    return 0;
}

