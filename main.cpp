#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Math/include/Transformations.h"
#include "Rendering/include/Camera.h"
#include "Geometry/include/ObjectFactory.h"
#include "Geometry/include/unitGeometricObjects/UnitCircle.h"
#include "Geometry/include/unitGeometricObjects/UnitCube.h"



/*
 * using the following book for the installation of OpenGl.
 * "Joey De Vries, Learn OpenGL: Learn modern OpenGL graphics programming in a step-by-step fashion. Kendall & Welling, 2020."
 *
 * 217-218
 */


int main() {

    Scene scene;
    Material material(0.989, 0.876, 0.399, 0.2);

    TransformationManager manager;
    manager.pushTranslation(-3, 0, 0);

    std::vector<std::shared_ptr<HitObject>> vector;
    vector.reserve(6);
    vector.emplace_back(ObjectFactory::createObject<UnitCircle>(material));
    vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager, material));

    manager.pushTranslation(3, 0, 0);
    manager.pushRotatePointZ(45);

    vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager, material));

    manager.pushScale(1, 3, 1);
    manager.pushTranslation(-3, -3, 10);

    vector.emplace_back(ObjectFactory::createObject<UnitCircle>(manager, material));

    manager.pushTranslation(0, 1.5, 0);
    manager.pushScale(0.2, 1.3, 1);


    vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager, material));

    Point3 point(0, 0, -15);
    Camera camera(1000, 1000, 60);
    scene.setObjects(vector);

    camera.initialize(scene, point);

    return 0;
}

