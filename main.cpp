#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Math/include/Transformations.h"
#include "Rendering/include/Camera.h"
#include "Geometry/include/ObjectFactory.h"
#include "Geometry/include/unitGeometricObjects/UnitCircle.h"
#include "Geometry/include/unitGeometricObjects/UnitCube.h"
#include "Rendering/include/Shaders/Material/FresnelMaterial.h"
#include "Shaders/CookTorranceShading.h"


/*
 * using the following book for the installation of OpenGl.
 * "Joey De Vries, Learn OpenGL: Learn modern OpenGL graphics programming in a step-by-step fashion. Kendall & Welling, 2020."
 *
 * 217-218
 */


int main() {

    Scene scene;
    std::shared_ptr<AbstractMaterial> material = std::make_shared<FresnelMaterial>(0.989, 0.876, 0.399, 0.2, 0.5, 0.1);

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

    Point3 lightPoint(0, 30, 0);
    Color3 Iar(255, 255, 255);
    Color3 Isr(255, 255, 255);


    std::vector<std::shared_ptr<LightSource>> lightVector;
    lightVector.reserve(1);
    lightVector.emplace_back(std::make_shared<LightSource>(lightPoint, Iar, Isr));


    scene.setObjects(vector);
    std::unique_ptr<CookTorranceShading> shader = std::make_unique<CookTorranceShading>();
    scene.setShader(std::move(shader));
    scene.setListOfLightsSourcePointers(lightVector);

    camera.initialize(scene, point);

    return 0;
}

