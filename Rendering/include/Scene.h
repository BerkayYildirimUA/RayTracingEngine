//
// Created by berka on 08/10/2024.
//

#ifndef RAYTRACINGENGINE_SCENE_H
#define RAYTRACINGENGINE_SCENE_H
#include "Core/include/Color3.h"
#include "Math/include/Point3.h"
#include "Core/include/Ray.h"

#include "Geometry/include/Intersection.h"
#include "Geometry/include/unitGeometricObjects/HitObject.h"
#include "Shaders/AbstractShader.h"
#include "Shaders/LightSource.h"


class Scene {

private:
    std::vector<std::shared_ptr<HitObject>> listOfObjectPointers;
    std::vector<std::shared_ptr<LightSource>> listOfLightsSourcePointers;

public:
    explicit Scene();

    Scene(const std::vector<std::shared_ptr<HitObject>> &listOfObjectPointers,
          const std::vector<std::shared_ptr<LightSource>> &listOfLightsSourcePointers);

    void setObjects(const std::vector<std::shared_ptr<HitObject>> &vector);

    void setListOfLightsSourcePointers(const std::vector<std::shared_ptr<LightSource>> &listOfLightsSourcePointers);

    [[nodiscard]] const std::vector<std::shared_ptr<HitObject>> &getListOfObjectPointers() const;

    [[nodiscard]] const std::vector<std::shared_ptr<LightSource>> &getListOfLightsSourcePointers() const;

    void loadScene(const std::string & filename);
};


#endif //RAYTRACINGENGINE_SCENE_H
