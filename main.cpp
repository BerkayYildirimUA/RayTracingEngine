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
    std::shared_ptr<AbstractMaterial> material1 = std::make_shared<FresnelMaterial>(1, 0, 0, 0.4, 0.4, 0.2);
    std::shared_ptr<AbstractMaterial> material2 = std::make_shared<FresnelMaterial>(0, 1, 0, 0.4, 0.4, 0.2);
    std::shared_ptr<AbstractMaterial> material3 = std::make_shared<FresnelMaterial>(0, 0, 1, 0.4, 0.4, 0.2);
    std::shared_ptr<AbstractMaterial> material4 = std::make_shared<FresnelMaterial>(1, 1, 1, 0.4, 0.4, 0.2);


    TransformationManager manager;
    std::vector<std::shared_ptr<HitObject>> vector;
    vector.reserve(17);


    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {

            // Translate each circle to its grid position
            manager.pushTranslation(x * 2, y * 2, 0);

            // Select material based on column (x value)
            std::shared_ptr<AbstractMaterial> material;
            if (x == 0) material = material1;
            else if (x == 1) material = material2;
            else if (x == 2) material = material3;
            else if (x == 3) material = material4;

            // Create the circle with the corresponding transformation and material
            vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager, material));
        }
    }


    manager.pushScale(30, 30, 30);
    vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager, material4));


    Point3 point(3, 3, -20);
    Camera camera(1000, 1000, 60);

    Point3 lightPoint(3, 3, -6);
    Color3 Iar(0.2, 0.2, 0.2);
    Color3 Isr(10000, 10000, 10000);


    std::vector<std::shared_ptr<LightSource>> lightVector;
    lightVector.reserve(4);
    lightVector.emplace_back(std::make_shared<LightSource>(lightPoint, Iar, Isr));
    //Point3 lightPoint2(-6, 6, -10);
    //lightVector.emplace_back(std::make_shared<LightSource>(lightPoint, Iar, Isr));
    //Point3 lightPoint3(6, -6, -10);
    //lightVector.emplace_back(std::make_shared<LightSource>(lightPoint, Iar, Isr));
    //Point3 lightPoint4(-6, -6, -10);
    //lightVector.emplace_back(std::make_shared<LightSource>(lightPoint, Iar, Isr));


    scene.setObjects(vector);
    std::unique_ptr<CookTorranceShading> shader = std::make_unique<CookTorranceShading>();
    scene.setShader(std::move(shader));
    scene.setListOfLightsSourcePointers(lightVector);

    camera.initialize(scene, point);

    return 0;
}

