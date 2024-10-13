//
// Created by berka on 08/10/2024.
//

#ifndef RAYTRACINGENGINE_COLOR3_H
#define RAYTRACINGENGINE_COLOR3_H


class Color3 {

public:
    float R, G, B;

    Color3() { R = G = B = 0; }

    Color3(float r, float g, float b) {
        R = r;
        G = g;
        B = b;
    }

    Color3(Color3 &color) {
        R = color.R;
        G = color.G;
        B = color.B;
    }

    void set(float r, float g, float b) {
        R = r;
        G = g;
        B = b;
    }

    void set(Color3 &color) {
        R = color.R;
        G = color.G;
        B = color.B;
    }

    void add(float r, float g, float b) {
        R += r;
        G += g;
        B += b;
    }

    void add(Color3 &src, Color3 &refl);
};


#endif //RAYTRACINGENGINE_COLOR3_H
