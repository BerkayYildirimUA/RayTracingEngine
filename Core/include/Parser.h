//
// Created by berka on 18/01/2025.
//

#ifndef RAYTRACINGENGINE_PARSER_H
#define RAYTRACINGENGINE_PARSER_H


#include "Geometry/include/unitGeometricObjects/HitObject.h"
#include "Math/include/TransformationManager.h"
#include "Shaders/LightSource.h"
#include "Shaders/Material/AbstractMaterial.h"

class Parser {

public:
    std::vector<std::shared_ptr<HitObject>> ParseFile(const std::string& filename);
    std::vector<std::shared_ptr<HitObject>> ParseFile(const std::string& filename, const TransformationManager& manager); //to change whole object
    std::vector<std::shared_ptr<LightSource>> ParseLights(const std::string& filename);

private:
    void ParseMaterial(std::ifstream& file, const std::string& name);
    std::shared_ptr<HitObject> ParseShape(std::ifstream &file, const std::string &type);
    std::shared_ptr<TransformationManager> ParseTransformations(std::ifstream& file);
    std::string ExtractShapeType(std::ifstream &file);
    std::shared_ptr<LightSource> ParseLight(std::ifstream& file);

    std::unordered_map<std::string, std::shared_ptr<AbstractMaterial>> materialMap;
    TransformationManager baseManger;
};


#endif //RAYTRACINGENGINE_PARSER_H
