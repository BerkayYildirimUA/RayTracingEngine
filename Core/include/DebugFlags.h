//
// Created by berka on 21/11/2024.
//

#ifndef RAYTRACINGENGINE_DEBUGFLAGS_H
#define RAYTRACINGENGINE_DEBUGFLAGS_H

class DebugFlags { 
private:
    static constexpr bool singleThreadMode = false;
    static constexpr bool turnOffAmbientColors = false;
    static constexpr bool turnOffSpecularColors = false;
    static constexpr bool turnOffDefusedColors = false;
    static constexpr bool turnOffShadows = false;
    static constexpr bool turnOffRefraction = false;
    static constexpr bool turnOffReflection = false;

public:
    DebugFlags(const DebugFlags &) = delete;

    DebugFlags &operator=(const DebugFlags &) = delete;

    static bool getSingleThreadMode() {
        return singleThreadMode;
    }

    static bool getTurnOffSpecularColors() {
        return turnOffSpecularColors;
    }

    static bool getTurnOffAmbientColors() {
        return turnOffAmbientColors;
    }

    static bool getTurnOffDefusedColors() {
        return turnOffDefusedColors;
    }

    static bool getTurnOffShadows() {
        return turnOffShadows;
    }

    static bool getTurnOffRefraction() {
        return turnOffRefraction;
    }

    static bool getTurnOffReflection() {
        return turnOffReflection;
    }

};


#endif //RAYTRACINGENGINE_DEBUGFLAGS_H
