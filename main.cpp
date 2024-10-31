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

    std::shared_ptr<AbstractMaterial> sky = std::make_shared<FresnelMaterial>(0.3, 0.4, 0.8, 0.3, 0.5, 1);
    std::shared_ptr<AbstractMaterial> gold = std::make_shared<FresnelMaterial>(0.989, 0.876, 0.399, 0.3, 0.15, 0.05);
    //std::shared_ptr<AbstractMaterial> silver = std::make_shared<FresnelMaterial>(0.25, 0.23, 0.18, 0.3, 0.3, 0.1);


    TransformationManager manager;
    std::vector<std::shared_ptr<HitObject>> vector;
    vector.reserve(201);

/*
    int numMatrices = 5;
    int innerGridSize = 4;
    double matrixSpacing = 12;
    int max = 5;

    for (int matrixIndex = 0; matrixIndex < numMatrices; ++matrixIndex) {

        double matrixXPos = (matrixIndex - numMatrices / 2) * matrixSpacing;

        double roughnessStep = 1.0 / max;

        for (int x = 0; x < innerGridSize; ++x) {
            double r = (x == 0 || x == 3) ? 1 : 0;
            double g = (x == 1 || x == 3) ? 1 : 0;
            double b = (x == 2 || x == 3) ? 1 : 0;

            for (int y = 0; y < max; ++y) {
                double ambient = y * roughnessStep;
                double roughness = matrixIndex * roughnessStep;

                // Calculate position for each object in the inner 5x5 grid
                double innerXPos = matrixXPos + (-3 + x * 2.5);
                double innerYPos = y * 2.5;

                // Apply transformations based on calculated positions
                manager.pushTranslation(innerXPos, innerYPos, 5);

                // Select material based on column (x value)
                std::shared_ptr<AbstractMaterial> material = std::make_shared<FresnelMaterial>(r, g, b, ambient, 0.6, roughness);

                // Create the circle with the corresponding transformation and material
                vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager, material));
            }
        }
    }

    for (int matrixIndex = 0; matrixIndex < numMatrices; ++matrixIndex) {

        double matrixXPos = (matrixIndex - numMatrices / 2) * matrixSpacing;

        double roughnessStep = 1.0 / max;

        for (int x = 0; x < innerGridSize; ++x) {
            double r = (x == 0 || x == 3) ? 1 : 0;
            double g = (x == 1 || x == 3) ? 1 : 0;
            double b = (x == 2 || x == 3) ? 1 : 0;

            for (int y = 0; y < max; ++y) {
                double ambient = y * roughnessStep;
                double roughness = matrixIndex * roughnessStep;

                // Calculate position for each object in the inner 5x5 grid
                double innerXPos = matrixXPos + (-3 + x * 2.5);
                double innerYPos = y * 2.2 - 15;

                // Apply transformations based on calculated positions
                manager.pushTranslation(innerXPos, innerYPos, 5);

                // Select material based on column (x value)
                std::shared_ptr<AbstractMaterial> material = std::make_shared<FresnelMaterial>(r, g, b, ambient, 0.6, roughness);

                // Create the circle with the corresponding transformation and material
                vector.emplace_back(ObjectFactory::createObject<UnitSphere>(manager, material));
            }
        }
    }
*/

    manager.pushTranslation(0, 0, 30);
    manager.pushScale(20, 20, 2);
    vector.emplace_back(ObjectFactory::createObject<UnitSphere>(manager, gold));


    manager.pushScale(100, 100, 100);
    vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager, sky));

    manager.pushTranslation(0, 0.6, 0);
    manager.pushScale(100, 0.1, 100);
    vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager, gold));

    Point3 point(0, 0, -70);
    Camera camera(1920, 1080, 60);
    //camera.pitch(20);
    //camera.yaw(20);


    Point3 lightPoint(80, 0, -70);
    Color3 Iar(0.2, 0.2, 0.2);
    Color3 Isr(10000, 10000, 10000);

    Point3 lightPoint2(-80, 0, -70);
    Color3 Iar2(0, 0, 0);
    Color3 Isr2(10000, 10000, 10000);

    Point3 lightPoint3(0, 0, 70);
    Color3 Iar3(0, 0, 0);
    Color3 Isr3(5000, 5000, 5000);


    std::vector<std::shared_ptr<LightSource>> lightVector;
    lightVector.reserve(4);
    lightVector.emplace_back(std::make_shared<LightSource>(lightPoint, Iar, Isr));
    lightVector.emplace_back(std::make_shared<LightSource>(lightPoint2, Iar2, Isr2));
    lightVector.emplace_back(std::make_shared<LightSource>(lightPoint3, Iar3, Isr3));
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

