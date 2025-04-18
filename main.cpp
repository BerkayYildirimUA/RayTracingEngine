#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Math/include/Transformations.h"
#include "Rendering/include/Camera.h"
#include "Geometry/include/ObjectFactory.h"
#include "Shaders/CookTorranceShading.h"
#include "Core/include/Parser.h"
#include "Textures/TextureFactory.h"



/*
 * using the following book for the installation of OpenGl.
 * "Joey De Vries, Learn OpenGL: Learn modern OpenGL graphics programming in a step-by-step fashion. Kendall & Welling, 2020."
 *
 * 217-218
 */


int main() {


    /*
    std::shared_ptr<AbstractMaterial> material1 = std::make_shared<FresnelMaterial>(1, 0, 0, 0.4, 0.4, 0.2);
    std::shared_ptr<AbstractMaterial> material2 = std::make_shared<FresnelMaterial>(0, 1, 0, 0.4, 0.4, 0.2);
    std::shared_ptr<AbstractMaterial> material3 = std::make_shared<FresnelMaterial>(0, 0, 1, 0.4, 0.4, 0.2);
    std::shared_ptr<AbstractMaterial> material4 = std::make_shared<FresnelMaterial>(1, 1, 1, 0.4, 0.4, 0.2);

    //std::shared_ptr<AbstractMaterial> sky = std::make_shared<FresnelMaterial>(0.3, 0.4, 0.8, 0.3, 0.5, 1);
    std::shared_ptr<AbstractMaterial> sky = std::make_shared<FresnelMaterial>(0.3, 0.4, 0.8, 0.3, 0.5, 1, 0.9, 0.3, 10000);
    std::shared_ptr<AbstractMaterial> brown = std::make_shared<FresnelMaterial>(0.6, 0.30, 0.15, 0.3, 0.75, 0.85, 0, 0, 100000);
    std::shared_ptr<AbstractMaterial> darkBrown = std::make_shared<FresnelMaterial>(0.3, 0.15, 0.075, 0.3, 0.75, 0.85, 0, 0, 100000);
    //std::shared_ptr<AbstractMaterial> gold = std::make_shared<FresnelMaterial>(0.989, 0.876, 0.399, 0.3, 0.35, 0.05);

    //std::shared_ptr<AbstractMaterial> silver = std::make_shared<FresnelMaterial>(0.25, 0.23, 0.18, 0.3, 0.3, 0.1);

*/



    Parser parser;
    //std::vector<std::shared_ptr<HitObject>> vector = parser.ParseFile("D:\\UA\\Semester7\\ComputerGraphics\\CppCode\\RayTracingEngine\\ObjectsData\\Objects\\streetLight\\streetLightPole.txt");

    std::vector<std::shared_ptr<HitObject>> vector = parser.ParseFile("D:\\UA\\Semester7\\ComputerGraphics\\CppCode\\RayTracingEngine\\ObjectsData\\Scenes\\dinnerScene");
    std::vector<std::shared_ptr<LightSource>> lightVector = parser.ParseLights("D:\\UA\\Semester7\\ComputerGraphics\\CppCode\\RayTracingEngine\\ObjectsData\\Lights\\lights.txt");



    //Camera camera(400, 400, 60); //1280×720p
    Camera camera(1920, 1080, 100);

    TransformationManager manager;
    manager.pushTranslation(2, 14, 0);

    std::shared_ptr<AbstractMaterial> material1 = std::make_shared<FresnelMaterial>(0, 0, 1, 0.2, 0.8, 1);


    vector.emplace_back(ObjectFactory::createObject<UnitCube>(manager, material1));


    Point3 point(0,15,2);
    camera.yaw(180);
    camera.pitch(-45);





    /*
    // show of this
  Point3 point(10,3,20);
    camera.yaw(160);
    camera.pitch(-10);

     // this
    Point3 point(0, 25,25);
    camera.yaw(180);
    camera.pitch(-45);

     */
/*
    camera.setNormalUpVector(Vector3(0,-0.939693,-0.34202));
    camera.setNormalRightVector(Vector3(1,0,0));
    camera.setNormalDistanceVector(Vector3 (0,-0.34202,0.939693));
*/
    Scene scene(vector, lightVector);

    camera.initialize(scene, point);

    return 0;
}

