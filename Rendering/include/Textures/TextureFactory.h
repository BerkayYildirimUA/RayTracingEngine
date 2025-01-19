//
// Created by berka on 19/01/2025.
//

#ifndef RAYTRACINGENGINE_TEXTUREFACTORY_H
#define RAYTRACINGENGINE_TEXTUREFACTORY_H

#include "unordered_map"
#include "iostream"
#include "functional"
#include "Core/include/Color3.h"

class TextureFactory {
private:
    std::unordered_map<std::string, std::function<Color3(double, double, double)>> textureMap;

    TextureFactory(){
        registerDefaultTextures();
    }

    void registerDefaultTextures();

public:

    TextureFactory(const TextureFactory&) = delete;
    TextureFactory& operator=(const TextureFactory&) = delete;

    static TextureFactory& getInstance() {
        static TextureFactory instance;
        return instance;
    }

    void registerTexture(const std::string& name, std::function<Color3(double, double, double)> texture) {
        textureMap[name] = texture;
    }

    std::function<Color3(double, double, double)> getTexture(const std::string& name) const {
        auto it = textureMap.find(name);
        if (it != textureMap.end()) {
            return it->second;
        }
        throw std::runtime_error("Unknown texture function: " + name);
    }

};


#endif //RAYTRACINGENGINE_TEXTUREFACTORY_H
