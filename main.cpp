#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Math/include/Transformations.h"
#include "Rendering/include/Camera.h"
#include "Geometry/include/ObjectFactory.h"
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

    //std::shared_ptr<AbstractMaterial> sky = std::make_shared<FresnelMaterial>(0.3, 0.4, 0.8, 0.3, 0.5, 1);
    std::shared_ptr<AbstractMaterial> sky = std::make_shared<FresnelMaterial>(0.3, 0.4, 0.8, 0.3, 0.5, 1, 0.2, 0.1, 10000);
    std::shared_ptr<AbstractMaterial> gold = std::make_shared<FresnelMaterial>(1, 1, 0, 0.3, 0.35, 0.05, 0.5, 0.2, 100000);
    //std::shared_ptr<AbstractMaterial> gold = std::make_shared<FresnelMaterial>(0.989, 0.876, 0.399, 0.3, 0.35, 0.05);

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

    /*manager.pushTranslation(0, 0, 30);
    manager.pushScale(60, 40, 20);
    vector.emplace_back(ObjectFactory::createObject<UnitSphere>(manager, gold));*/
/*
    manager.pushTranslation(0, 0, 10);
    manager.pushScale(1, 8, 2);
    manager.pushRotatePointY(180);
    manager.pushRotatePointZ(29);
*/

/*
    manager.pushScale(9, 9, 9);
    vector.emplace_back(ObjectFactory::createObject<UnitSphere>(manager, gold));
*/

  /*  manager.pushScale(1, 20, 1);
    manager.pushTranslation(0, 0, 30);
    vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager, material1));*/

/*
    manager.pushTranslation(0, 40, -100);
    manager.pushScale(20, 20, 1);
    vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager, material2));
*/



/*
    manager.pushScale(3, 3, 3);
    auto cube1 = ObjectFactory::createObject<UnitCube>(manager, gold);
    manager.pushTranslation(1.5, 0, 0);
    manager.pushScale(3, 3, 3);
    auto cube2 = ObjectFactory::createObject<UnitSphere>(manager, material1);


    vector.emplace_back(ObjectFactory::createBoolObject<IntersectionBool>(cube2, cube1));*/
    //vector.push_back(cube1);
    //vector.push_back(cube2);




    manager.pushScale(40, 18, 1); // Scale [40, 18, 1]
    manager.pushScale(0.5, 0.5, 0.5);     // Scale
    auto baseCube = ObjectFactory::createObject<UnitCube>(manager, gold); // Creates and resets

    std::vector<std::shared_ptr<PrimitiveObjects>> unionCubes;

    manager.pushTranslation(15, 4, 0); // Translate
    manager.pushScale(5, 5, 2);        // Scale
    manager.pushScale(0.5, 0.5, 0.5);     // Scale
    unionCubes.emplace_back(ObjectFactory::createObject<UnitCube>(manager, gold)); // Creates and resets

    manager.pushTranslation(15, -4, 0); // Translate
    manager.pushScale(5, 5, 2);         // Scale
    manager.pushScale(0.5, 0.5, 0.5);     // Scale
    unionCubes.emplace_back(ObjectFactory::createObject<UnitCube>(manager, gold)); // Creates and resets

    manager.pushTranslation(8, 4, 0); // Translate
    manager.pushScale(5, 5, 2);       // Scale
    manager.pushScale(0.5, 0.5, 0.5);     // Scale
    unionCubes.emplace_back(ObjectFactory::createObject<UnitCube>(manager, gold)); // Creates and resets

    manager.pushTranslation(8, -4, 0); // Translate
    manager.pushScale(5, 5, 2);        // Scale
    manager.pushScale(0.5, 0.5, 0.5);     // Scale
    unionCubes.emplace_back(ObjectFactory::createObject<UnitCube>(manager, gold)); // Creates and resets

    manager.pushTranslation(-10, 0, 0.8); // Translate
    manager.pushScale(15, 14, 1);         // Scale
    manager.pushScale(0.5, 0.5, 0.5);     // Scale
    unionCubes.emplace_back(ObjectFactory::createObject<UnitCube>(manager, gold)); // Creates and resets

    std::shared_ptr<HitObject> unionObject = unionCubes[0];
    for (size_t i = 1; i < unionCubes.size(); ++i) {
        unionObject = ObjectFactory::createBoolObject<UnionBool>(unionObject, unionCubes[i]);
    }

    auto diffObject = ObjectFactory::createBoolObject<DifferenceBool>(baseCube, unionObject);

    vector.emplace_back(diffObject);



    manager.pushTranslation(1, 6, 1);
    manager.pushScale(0.6, 0.6, 1);
    manager.pushScale(0.5, 0.5, 0.5);
    auto extraCube1 = ObjectFactory::createObject<UnitCube>(manager, gold);

    diffObject = ObjectFactory::createBoolObject<UnionBool>(diffObject, extraCube1);

    manager.pushTranslation(1.0085, 5.301, 1.4); // Translate
    manager.pushScale(0.6, 2, 0.2);              // Scale
    manager.pushScale(0.5, 0.5, 0.5);     // Scale
    auto extraCube2 = ObjectFactory::createObject<UnitCube>(manager, gold);

    diffObject = ObjectFactory::createBoolObject<UnionBool>(diffObject, extraCube2);


    vector.emplace_back(diffObject);

    /*
    manager.pushTranslation(1.0085, 5.301, 1.4); // Translate
    manager.pushScale(0.6, 2, 0.2);              // Scale
    manager.pushScale(0.5, 0.5, 0.5);     // Scale
    auto extraCube2 = ObjectFactory::createObject<UnitCube>(manager, gold); // Creates and resets

    auto finalObject = ObjectFactory::createBoolObject<UnionBool>(diffObject, extraCube1);
     finalObject = ObjectFactory::createBoolObject<UnionBool>(finalObject,extraCube2 );


// Final Union (Difference + Extra Cubes)
   // auto finalObject = ObjectFactory::createBoolObject<UnionBool>(extraCube2, extraCube1);
   // finalObject = ObjectFactory::createBoolObject<UnionBool>(finalObject, extraCube1);

// Store the Final Object
    vector.emplace_back(finalObject);*/


/*
    manager.pushScale(3, 3, 3);
    auto cube1 = ObjectFactory::createObject<UnitCube>(manager, gold);

    //manager.pushRotatePointZ(45);
    manager.pushScale(2, 2, 2);
    manager.pushTranslation(0, 0, 0.8);
    //manager.pushRotatePointX(45);
    //manager.pushRotatePointY(45);
    auto cube2 = ObjectFactory::createObject<UnitCube>(manager, gold);

    auto finalObject = ObjectFactory::createBoolObject<DifferenceBool>(cube1, cube2);

    vector.emplace_back(finalObject);
*/
    manager.pushScale(1000, 1000, 1000);
    vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager, sky));

    //manager.pushTranslation(0, 0, 0);
    //manager.pushScale(100, 0.1, 100);
    //vector.emplace_back(ObjectFactory::createObject<UnitSphere>( gold));

    //Camera camera(1920, 1080, 60);


    Camera camera(400, 400, 60); //1280×720p

    Point3 point(8, 0, 30);
    //Camera camera(1280, 720, 60);
   // camera.yaw(146.31);
    //camera.pitch(-40);
  //  camera.roll(90);
    camera.roll(90);
    camera.yaw(180);
    //camera.yaw(20);

    //camera.pitch(180);

    //camera.pitch(-30);
    //camera.yaw(30);

    Point3 lightPoint(0, 0, -20);
    Color3 Iar(0.2, 0.2, 0.2);
    Color3 Isr(10000, 10000, 10000);

    Point3 lightPoint2(-80, 0, -70);
    Color3 Iar2(0, 0, 0);
    Color3 Isr2(10000, 10000, 10000);

    Point3 lightPoint3(0, 0, 30);
    Color3 Iar3(3, 3, 3);
    Color3 Isr3(5000, 5000, 5000);


    std::vector<std::shared_ptr<LightSource>> lightVector;
    lightVector.reserve(4);
    lightVector.emplace_back(std::make_shared<LightSource>(lightPoint3, Iar, Isr));
    //lightVector.emplace_back(std::make_shared<LightSource>(lightPoint2, Iar2, Isr2));
    //lightVector.emplace_back(std::make_shared<LightSource>(lightPoint3, Iar3, Isr3));
    //lightVector.emplace_back(std::make_shared<LightSource>(lightPoint, Iar, Isr));
    //Point3 lightPoint3(6, -6, -10);
    //lightVector.emplace_back(std::make_shared<LightSource>(lightPoint, Iar, Isr));
    //Point3 lightPoint4(-6, -6, -10);
    //lightVector.emplace_back(std::make_shared<LightSource>(lightPoint, Iar, Isr));


    scene.setObjects(vector);
    scene.setListOfLightsSourcePointers(lightVector);

    camera.initialize(scene, point);

    return 0;
}

