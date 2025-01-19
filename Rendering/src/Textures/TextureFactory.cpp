//
// Created by berka on 19/01/2025.
//

#include "Rendering/include/Textures/TextureFactory.h"

void TextureFactory::registerDefaultTextures() {

    registerTexture("default", [](double x, double y, double z) {
        return Color3(1, 1, 1);
    });

    registerTexture("checker", [](double x, double y, double z) {

        auto checkerPattern = [](double coord) {
            double scaled = coord * 3.0;
            return static_cast<int>(std::floor(scaled + 0.5)) % 2;
        };


        int pattern = checkerPattern(x * 10) + checkerPattern(y * 10) + checkerPattern(z * 10);

        return (pattern % 2 == 0) ? Color3(1, 1, 1) : Color3(0, 0, 0);
    });

    registerTexture("gradient", [](double x, double y, double z) {
        return Color3((x + 1) / 2, (y + 1) / 2, (z + 1) / 2); // Normalize [-1, 1] to [0, 1]
    });

    registerTexture("radial", [](double x, double y, double z) {
        double dist = sqrt(x * x + y * y + z * z); // Euclidean distance from origin
        dist = std::clamp(dist, 0.0, 1.0);         // Ensure distance stays within [0, 1]
        return Color3(dist, dist, dist);           // Grayscale gradient
    });

    registerTexture("marble", [](double x, double y, double z) {
        auto turbulence = [](double x, double y, double z, int octaves) {
            double value = 0.0, scale = 1.0;
            for (int i = 0; i < octaves; ++i) {
                value += fabs(sin(x * scale) * sin(y * scale) * sin(z * scale)) / scale;
                scale *= 2.0;
            }
            return value;
        };

        double noise = turbulence(x, y, z, 5);
        double veins = sin((x + noise * 0.5) * 10.0) + noise * 0.5;
        veins = fabs(veins);
        veins = veins - floor(veins);

        return Color3(veins, veins, veins);
    });

    registerTexture("wood", [](double x, double y, double z) {
        auto turbulence = [](double x, double y, double z, int octaves) {
            double value = 0.0, scale = 1.0;
            for (int i = 0; i < octaves; ++i) {
                value += fabs(sin(x * scale) * sin(y * scale) * sin(z * scale)) / scale;
                scale *= 2.0;
            }
            return value;
        };

        double radius = sqrt(x * x + z * z);
        double noise = turbulence(x, y, z, 3);
        double rings = sin((radius + noise * 0.1) * 20.0);

        rings = (rings + 1.0) * 0.5;
        Color3 woodColor = Color3(0.52, 0.37, 0.26);
        Color3 ringColor = Color3(0.64, 0.5, 0.35);

        return rings * woodColor + (1.0 - rings) * ringColor;
    });



}
