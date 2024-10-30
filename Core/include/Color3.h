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

    Color3(double r, double g, double b) {
        colors << r, g, b;
    }


    Color3(const Color3 &color) {
        colors = color.colors;
    }

    explicit Color3(const Eigen::Vector3d &color) {
        colors = color;
    }

    void set(double r, double g, double b) {
        colors.x() = r;
        colors.y() = g;
        colors.z() = b;
    }

    void set(const Color3 &color) {
        colors = color.colors;

    }

    void add(double r, double g, double b) {
        colors.x() += r;
        colors.y() += g;
        colors.z() += b;
    }

    void add(Color3 &src, Color3 &refl);

    const double &getRed() const {
        return colors[0];
    }

    const double &getGreen() const {
        return colors[1];
    }


    const double &getBlue() const {
        return colors[2];
    }

    Color3 operator+(const Color3 &other) const {
        return Color3(this->colors + other.colors);
    }
};


#endif //RAYTRACINGENGINE_COLOR3_H
