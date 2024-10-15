//
// Created by berka on 14/10/2024.
//

#ifndef RAYTRACINGENGINE_TRANSFORMATIONMANAGER_H
#define RAYTRACINGENGINE_TRANSFORMATIONMANAGER_H

#include "stack"
#include "Eigen/Core"
#include "optional"

/*
 * TODO: make inverse and normal at the same time.
 */

class TransformationManager {
private:
    std::stack<Eigen::Matrix<double, 4, 4>> transformStack;
    std::optional<bool> isInverse;


public:
    TransformationManager();

    void pushTranslation(double x, double y, double z);

    void pushScale(double x, double y, double z);

    void pushRotatePointX(double angle);

    void pushRotatePointY(double angle);

    void pushRotatePointZ(double angle);

    void pushInverseTranslation(double x, double y, double z);

    void pushInverseScale(double x, double y, double z);

    void pushInverseRotatePointX(double angle);

    void pushInverseRotatePointY(double angle);

    void pushInverseRotatePointZ(double angle);


    Eigen::Matrix<double, 4, 4> getTotalTransformation();


};


#endif //RAYTRACINGENGINE_TRANSFORMATIONMANAGER_H
