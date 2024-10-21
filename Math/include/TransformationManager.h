//
// Created by berka on 14/10/2024.
//

#ifndef RAYTRACINGENGINE_TRANSFORMATIONMANAGER_H
#define RAYTRACINGENGINE_TRANSFORMATIONMANAGER_H

#include "stack"
#include "Eigen/Core"
#include "optional"
#include "utility"

/*
 * TODO: make inverse and normal at the same time.
 */

class TransformationManager {
private:
    std::stack<Eigen::Matrix4d> transformStack;
    std::stack<Eigen::Matrix4d> invTransformStack;


public:
    TransformationManager() = default;

    //TransformationManager(const TransformationManager& other) : transformStack(other.transformStack), invTransformStack(other.invTransformStack) {}

    void pushTranslation(double x, double y, double z);

    void pushScale(double x, double y, double z);

    void pushRotatePointX(double angle);

    void pushRotatePointY(double angle);

    void pushRotatePointZ(double angle);

    std::pair<Eigen::Matrix4d, Eigen::Matrix4d> getTotalTransformation();

private:

    void pushInverseTranslation(double x, double y, double z);

    void pushInverseScale(double x, double y, double z);

    void pushInverseRotatePointX(double angle);

    void pushInverseRotatePointY(double angle);

    void pushInverseRotatePointZ(double angle);

};


#endif //RAYTRACINGENGINE_TRANSFORMATIONMANAGER_H
