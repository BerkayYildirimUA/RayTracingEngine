//
// Created by berka on 27/10/2024.
//

#ifndef RAYTRACINGENGINE_LIGHTSOURCE_H
#define RAYTRACINGENGINE_LIGHTSOURCE_H

#include "Point3.h"
#include "Color3.h"

class LightSource {
public:
    Point3 location;
    Color3 Iar;
    Color3 Isr;

    LightSource(Point3 &location,  Color3& iar,  Color3& isr);

};


#endif //RAYTRACINGENGINE_LIGHTSOURCE_H
