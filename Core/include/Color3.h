//
// Created by berka on 08/10/2024.
//

#ifndef RAYTRACINGENGINE_COLOR3_H
#define RAYTRACINGENGINE_COLOR3_H

#include "Eigen/Core"

class Color3 {

public:
    Eigen::Vector3d colors;

    Color3() { colors << 0, 0, 0; }

    Color3(float r, float g, float b) {
        colors << r, g, b;
    }

    Color3(const Color3 &color) {
        colors = color.colors;
    }

    void set(float r, float g, float b) {
        colors.x() = r;
        colors.y() = g;
        colors.z() = b;
    }

    void set(const Color3 &color) {
        colors = color.colors;

    }

    void add(float r, float g, float b) {
        colors.x() += r;
        colors.y() += g;
        colors.z() += b;
    }

    void add(Color3 &src, Color3 &refl);
};


#endif //RAYTRACINGENGINE_COLOR3_H
