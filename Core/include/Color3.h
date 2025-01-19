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

    void add(Color3 &other){
        this->add(other.getRed(), other.getGreen(), other.getBlue());
    }

    void add(const Color3 &other){
        this->add(other.getRed(), other.getGreen(), other.getBlue());
    }

    double difference(const Color3 &other) const {

        double redDiff = this->getRed() - other.getRed();
        double greenDiff = this->getGreen() - other.getGreen();
        double blueDiff = this->getBlue() - other.getBlue();



        return std::sqrt(redDiff * redDiff + greenDiff * greenDiff + blueDiff * blueDiff);
    }


    const double getRed() const {
        return colors[0];
    }

    const double getGreen() const {
        return colors[1];
    }


    const double getBlue() const {
        return colors[2];
    }

    const double getColor(int i) const {
        return colors[i];
    }

    Color3 operator+(const Color3 &other) const {
        return Color3(this->colors + other.colors);
    }

    Color3 operator/(double number) const {
        return {this->getRed()/number, this->getGreen()/number, this->getBlue()/number};
    }

    Color3 operator*(double number) const {
        return {this->getRed()*number, this->getGreen()*number, this->getBlue()*number};
    }

    friend Color3 operator*(double scalar, const Color3& obj);

};



#endif //RAYTRACINGENGINE_COLOR3_H
