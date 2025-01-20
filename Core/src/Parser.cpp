//
// Created by berka on 18/01/2025.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <stack>

#include "Core/include/Parser.h"
#include "Shaders/Material/AbstractMaterial.h"
#include "Shaders/Material/FresnelMaterial.h"
#include "ObjectFactory.h"
#include "Textures/TextureFactory.h"

std::vector<std::shared_ptr<HitObject>> Parser::ParseFile(const std::string &filename) {
    std::ifstream file(filename);

    std::vector<std::shared_ptr<HitObject>> vector;

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return vector;
    }

    std::string line;
    while (std::getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t"));

        // Skip lines starting with '#'
        if (!line.empty() && line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "material") {
            std::string materialName;
            iss >> materialName;
            ParseMaterial(file, materialName);
        } else if (keyword == "shape") {
            std::string type;
            iss >> type;
            auto shape = ParseShape(file, type);
            vector.push_back(shape);
        } else if (keyword == "ObjectFile") {
            std::string nestedFilename;
            iss >> nestedFilename;

            std::shared_ptr<TransformationManager> nestedManager = ParseTransformations(file);
            Parser newParser;

            auto nestedObjects = newParser.ParseFile(nestedFilename, *nestedManager);
            vector.insert(vector.end(), nestedObjects.begin(), nestedObjects.end());
        }
    }

    return vector;
}

std::vector<std::shared_ptr<HitObject>> Parser::ParseFile(const std::string &filename, const TransformationManager& manager) {
    baseManger = manager;
    return ParseFile(filename);
}

void Parser::ParseMaterial(std::ifstream &file, const std::string &name) {
    double r = 0, g = 0, b = 0;
    double emission_r = 0, emission_g = 0, emission_b = 0; //colors of emissive objects
    double ambient = 0, diffuse = 0, rough = 0;
    double transparency = 0, shininess = 0, speed = 0;
    bool extended = false;
    std::string texture = "default";

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "indexOfRefraction") {
            iss >> r >> g >> b;
        } else if (keyword == "ambientLightFactor") {
            iss >> ambient;
        } else if (keyword == "defusedLightFactor") {
            iss >> diffuse;
        } else if (keyword == "roughness") {
            iss >> rough;
        } else if (keyword == "transparency") {
            iss >> transparency;
            extended = true;
        } else if (keyword == "shininess") {
            iss >> shininess;
            extended = true;
        } else if (keyword == "speedOfLight") {
            iss >> speed;
            extended = true;
        } else if (keyword == "texture") {
            iss >> texture;
        } else if (keyword == "emission") {
            iss >> emission_r >> emission_g >> emission_b;
        } else if (keyword == "}") {
            break;
        }
    }

    std::shared_ptr<FresnelMaterial> material;

    if (extended) {
        material = std::make_shared<FresnelMaterial>(r, g, b, ambient, diffuse, rough, transparency, shininess, speed);
    } else {
        material = std::make_shared<FresnelMaterial>(r, g, b, ambient, diffuse, rough);
    }

    try {
        material->setTextureFunction(TextureFactory::getInstance().getTexture(texture));
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("Error in material '" + name + "': " + e.what());
    }

    if (emission_r != 0 || emission_g != 0 || emission_b != 0) {
        material->emission = Color3(emission_r, emission_g, emission_b); // quick and dirt solution, don't want to change my constructor this late in the project
    }

    materialMap[name] = material;

}

std::shared_ptr<HitObject> Parser::ParseShape(std::ifstream &file, const std::string &type) {
    std::string line;
    std::string materialName;
    double s = 1; // for cylinder
    std::shared_ptr<TransformationManager> manager = nullptr;
    std::shared_ptr<HitObject> shape = nullptr;
    std::shared_ptr<HitObject> left = nullptr;
    std::shared_ptr<HitObject> right = nullptr;

    bool didLeft = false;
    bool didRight = false;

    // Parse transformations, material, and recursive shapes
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "transformations") {
            manager = ParseTransformations(file);
        } else if (keyword == "material") {
            iss >> materialName;
        } else if (type == "Cylinder" && keyword == "s") {
            iss >> s;
        } else if (keyword == "left" || keyword == "right") {
            auto componentType = ExtractShapeType(file); // Read type of the nested shape
            if (keyword == "left") {
                left = ParseShape(file, componentType);
                didLeft = true;
            } else if (keyword == "right") {
                right = ParseShape(file, componentType);
                didRight = true;
            }
        } else if (keyword == "}" && (didRight == didLeft)) {
            break;
        }
    }

    if (type == "Sphere") {
        return ObjectFactory::createObject<UnitSphere>(*manager, materialMap[materialName]);
    } else if (type == "Cube") {
        return ObjectFactory::createObject<UnitCube>(*manager, materialMap[materialName]);
    } else if (type == "Cylinder") {
        return ObjectFactory::createObject<UnitCylinder>(*manager, materialMap[materialName], s);
    } else if (type == "BooleanUnion") {
        return ObjectFactory::createBoolObject<UnionBool>(left, right);
    } else if (type == "BooleanIntersection") {
        return ObjectFactory::createBoolObject<IntersectionBool>(left, right);
    } else if (type == "BooleanDifference") {
        return ObjectFactory::createBoolObject<DifferenceBool>(left, right);
    }


    return shape;
}

std::string Parser::ExtractShapeType(std::ifstream &file) {
    std::string line;
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string keyword, type;
        iss >> keyword >> type;
        if (keyword == "shape") {
            return type;
        }
    }
    throw std::runtime_error("Failed to extract shape type");
}


std::shared_ptr<TransformationManager> Parser::ParseTransformations(std::ifstream &file) {
    auto manager = std::make_shared<TransformationManager>(baseManger);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "translate") {
            double x, y, z;
            iss >> x >> y >> z;
            manager->pushTranslation(x, y, z);
        } else if (keyword == "scale") {
            double x, y, z;
            iss >> x >> y >> z;
            manager->pushScale(x, y, z);
        } else if (keyword == "rotate") {
            std::string axis;
            double angle;
            iss >> axis >> angle;
            if (axis == "X") manager->pushRotatePointX(angle);
            if (axis == "Y") manager->pushRotatePointY(angle);
            if (axis == "Z") manager->pushRotatePointZ(angle);
        } else if (keyword == "}") {
            break;
        }
    }

    return manager;

}

std::vector<std::shared_ptr<LightSource>> Parser::ParseLights(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::vector<std::shared_ptr<LightSource>> lightVector;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "Light") {
            lightVector.emplace_back(ParseLight(file));
        }
    }

    return lightVector;
}

std::shared_ptr<LightSource> Parser::ParseLight(std::ifstream &file) {
    Point3 location;
    Color3 ambientIntensity;
    Color3 specularIntensity;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "location") {
            double x, y, z;
            iss >> x >> y >> z;
            location = Point3(x, y, z);
        } else if (keyword == "ambientIntensity") {
            double r, g, b;
            iss >> r >> g >> b;
            ambientIntensity = Color3(r, g, b);
        } else if (keyword == "specularIntensity") {
            double r, g, b;
            iss >> r >> g >> b;
            specularIntensity = Color3(r, g, b);
        } else if (keyword == "}") {
            break; // End of Light block
        }
    }

    return std::make_shared<LightSource>(location, ambientIntensity, specularIntensity);
}
