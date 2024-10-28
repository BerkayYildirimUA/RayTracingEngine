//
// Created by berka on 27/10/2024.
//

#include <utility>

#include "Rendering/include/Shaders/LightSource.h"

LightSource::LightSource(Point3 &location,  Color3& iar,  Color3& isr) : location(std::move(location)), Iar(iar), Isr(isr) {}
