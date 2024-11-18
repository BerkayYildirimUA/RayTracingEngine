//
// Created by berka on 27/10/2024.
//

#ifndef RAYTRACINGENGINE_ABSTRACTMATERIAL_H
#define RAYTRACINGENGINE_ABSTRACTMATERIAL_H


class AbstractMaterial {
public:
    double transparency = 0;
    double shininess = 0;
    double speedOfLight = 1000;


    AbstractMaterial(double transparency, double shininess, double speedOfLight);

    AbstractMaterial();

    virtual ~AbstractMaterial() = default;
};


#endif //RAYTRACINGENGINE_ABSTRACTMATERIAL_H
