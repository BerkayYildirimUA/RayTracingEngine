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
        return Color3((x + 1) / 2, (y + 1) / 2, (z + 1) / 2);
    });

    registerTexture("radial", [](double x, double y, double z) {
        double dist = sqrt(x * x + y * y + z * z);
        dist = std::clamp(dist, 0.0, 1.0);
        return Color3(dist, dist, dist);
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

    registerTexture("rusticWood", [](double x, double y, double z) {
        auto turbulence = [](double x, double y, double z, int octaves) {
            double value = 0.0, scale = 1.0;
            for (int i = 0; i < octaves; ++i) {
                value += fabs(sin(x * scale) * sin(y * scale) * sin(z * scale)) / scale;
                scale *= 2.0;
            }
            return value;
        };

        double radius = sqrt(x * x + z * z);
        double noise = turbulence(x, y, z, 5);
        double rings = sin((radius + noise * 0.1) * 40.0);

        rings = (rings + 1.0) * 0.5;

        Color3 baseColor(0.35, 0.22, 0.15); // darker brown
        Color3 ringColor(0.50, 0.36, 0.25); // lighter brown

        return rings * baseColor + (1.0 - rings) * ringColor;
    });

    registerTexture("woodPlanksOrientedNormalized", [](double x, double y, double z) {
        const double EPSILON = 1e-3;
        bool runPlanksAlongX = (std::fabs(z - 1.0) < EPSILON || std::fabs(z + 1.0) < EPSILON);

        double nx = (x + 1.0) * 0.5;
        double ny = (y + 1.0) * 0.5;
        double nz = (z + 1.0) * 0.5;

        double coord = runPlanksAlongX ? nx : nz;

        double plankCount = 30.0;

        double plankPosition = std::fmod(coord * plankCount, 1.0);

        double gapThickness = 0.02;
        if (plankPosition < gapThickness) {
            return Color3(0.05, 0.05, 0.05);
        }

        auto pseudoRandom = [](int val) {
            val = (val << 13) ^ val;
            double r = 1.0 - ((val * (val * val * 15731 + 789221) + 1376312589)
                              & 0x7fffffff) / 1073741824.0;
            return r;
        };
        int plankIndex = static_cast<int>(std::floor(coord * plankCount));
        double variation = (pseudoRandom(plankIndex) - 0.5) * 0.08;

        double dx, dz;
        if (runPlanksAlongX) {
            // Use YZ-plane
            double dy = ny - 0.5;
            double dz_ = nz - 0.5;
            dx = dy;
            dz = dz_;
        } else {
            // Use XZ-plane
            double dx_ = nx - 0.5;
            double dz_ = nz - 0.5;
            dx = dx_;
            dz = dz_;
        }
        double radius = std::sqrt(dx * dx + dz * dz);

        auto turbulence = [&](double px, double py, double pz, int octaves) {
            double value = 0.0;
            double scale = 1.0;
            for (int i = 0; i < octaves; ++i) {
                value += std::fabs(std::sin(px * scale) *
                                   std::sin(py * scale) *
                                   std::sin(pz * scale)) / scale;
                scale *= 2.0;
            }
            return value;
        };

        double noise = turbulence(nx, ny, nz, 4);

        double frequency = 20.0;
        double rings = std::sin((radius + noise * 0.1) * frequency);
        rings = (rings + 1.0) * 0.5; // map [-1..1] to [0..1]

        Color3 baseColor(0.52 + variation, 0.37 + variation, 0.26 + variation);
        Color3 ringColor(0.65 + variation, 0.50 + variation, 0.35 + variation);

        Color3 finalColor = rings * baseColor + (1.0 - rings) * ringColor;

        auto clampColor = [](const Color3& c) {
            return Color3(
                    std::clamp(c.getRed(), 0.0, 1.0),
                    std::clamp(c.getGreen(), 0.0, 1.0),
                    std::clamp(c.getBlue(), 0.0, 1.0)
            );
        };

        return clampColor(finalColor);
    });

    registerTexture("subtleWoodDesk", [](double x, double y, double z) {
        auto turbulence = [](double xx, double yy, double zz, int octaves) {
            double value = 0.0;
            double scale = 1.0;
            for (int i = 0; i < octaves; ++i) {
                value += std::fabs(std::sin(xx * scale) *
                                   std::sin(yy * scale) *
                                   std::sin(zz * scale)) / scale;
                scale *= 2.0;
            }
            return value;
        };

        double scaledX = x * 0.5;
        double scaledY = y * 0.5;
        double scaledZ = z * 0.5;

        double noiseValue = turbulence(scaledX, scaledY, scaledZ, 25);

        double grainFrequency = 20.0;
        double noiseStrength  = 0.8;

        double rawGrain = std::sin((x + noiseValue * noiseStrength) * grainFrequency);

        double grain = 0.5 + 0.5 * rawGrain;

        Color3 colorA(0.55, 0.42, 0.30);
        Color3 colorB(0.50, 0.38, 0.27);


        double blendFactor = grain;
        Color3 finalColor = blendFactor * colorA + (1.0 - blendFactor) * colorB;


        double highlight = 0.02 * std::sin((z + noiseValue * 0.5) * 10.0);
        finalColor.set(std::clamp(finalColor.getRed() + highlight, 0.0, 1.0),
                       std::clamp(finalColor.getGreen() + highlight, 0.0, 1.0),
                       std::clamp(finalColor.getBlue() + highlight, 0.0, 1.0));

        return finalColor;
    });

    registerTexture("denseWoodDeskNoPattern", [](double x, double y, double z) {
        auto turbulence = [](double xx, double yy, double zz, int octaves) {
            double value = 0.0;
            double scale = 1.0;
            for (int i = 0; i < octaves; ++i) {
                value += std::fabs(std::sin(xx * scale) *
                                   std::sin(yy * scale) *
                                   std::sin(zz * scale)) / scale;
                scale *= 2.0;
            }
            return value;
        };

        double scaledX = x * 15.0;
        double scaledY = y * 15.0;
        double scaledZ = z * 15.0;

        double baseFrequency = 50.0;
        double noise = turbulence(scaledX, scaledY, scaledZ, 6);
        double variableFrequency = baseFrequency + noise * 5.0;

        double grain = std::sin((scaledX + noise * 0.3) * variableFrequency);

        grain = 0.5 + 0.5 * grain;

        double swirlFrequency = 10.0;
        double swirl = std::sin((scaledZ + noise) * swirlFrequency);
        swirl = 0.5 + 0.5 * swirl;

        double layeredGrain = 0.6 * grain + 0.4 * swirl;

        Color3 baseColor(0.58 / 2, 0.44 / 2, 0.34 / 2);
        Color3 highlightColor(0.7, 0.52, 0.4);
        double colorVariation = 0.05 * turbulence(scaledX, scaledY, scaledZ, 3);

        Color3 finalColor = layeredGrain * highlightColor + (1.0 - layeredGrain) * baseColor;

        finalColor.set(std::clamp(finalColor.getRed() + colorVariation, 0.0, 1.0),
                       std::clamp(finalColor.getGreen() + colorVariation, 0.0, 1.0),
                       std::clamp(finalColor.getBlue() + colorVariation, 0.0, 1.0));

        return finalColor;
    });


    registerTexture("porcelain", [](double x, double y, double z) {
            double scaledX = x * 8.0;
            double scaledY = y * 8.0;
            double scaledZ = z * 8.0;

            double pattern = 0.5 + 0.5 * std::sin(scaledX + std::sin(scaledY) * 0.3);

            auto softTurbulence = [](double xx, double yy, double zz) {
                return 0.1 * std::sin(xx * 5.0) + 0.1 * std::sin(yy * 5.0) + 0.1 * std::sin(zz * 5.0);
            };
            double noise = softTurbulence(scaledX, scaledY, scaledZ);

            double finalPattern = pattern + noise * 0.2;

            Color3 baseColor(0.85, 0.9, 1.0);  // Light blue
            Color3 lineColor(0.8, 0.85, 0.95); // Subtler blue for lines

            Color3 finalColor = finalPattern * lineColor + (1.0 - finalPattern) * baseColor;

            finalColor.set(std::clamp(finalColor.getRed(), 0.0, 1.0),
                           std::clamp(finalColor.getGreen(), 0.0, 1.0),
                           std::clamp(finalColor.getBlue(), 0.0, 1.0));

            return finalColor;
        });




    }
