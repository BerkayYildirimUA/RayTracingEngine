//
// Created by berka on 27/10/2024.
//

#include "Rendering/include/Shaders/Material/AbstractMaterial.h"

AbstractMaterial::AbstractMaterial(double transparency, double shininess, double speedOfLight) : transparency(transparency),
                                                                            shininess(shininess), speedOfLight(speedOfLight) {}

AbstractMaterial::AbstractMaterial() = default;
