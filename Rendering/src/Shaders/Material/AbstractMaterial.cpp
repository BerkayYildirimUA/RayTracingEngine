//
// Created by berka on 27/10/2024.
//

#include "Rendering/include/Shaders/Material/AbstractMaterial.h"

AbstractMaterial::AbstractMaterial(double transparency, double shininess, double speedOfLight) : transparency(transparency),
                                                                            shininess(shininess), speedOfLight(speedOfLight) {}

AbstractMaterial::AbstractMaterial() = default;

void AbstractMaterial::setTextureFunction(const std::function<Color3(double, double, double)> &func) {
    textureFunction = func;
}

Color3 AbstractMaterial::getTexture(double x, double y, double z) const {
    if (textureFunction) {
        return textureFunction(x, y, z);
    }

    return {1.0, 1.0, 1.0};
}

Color3 AbstractMaterial::getTexture(Point3 point) const {
    return getTexture(point.getX(), point.getY(), point.getZ());
}
