//
// Created by berka on 14/10/2024.
//

#include <iostream>
#include "Math/include/TransformationManager.h"
#include "Math/include/Transformations.h"
#include "Math/include/InverseTransformations.h"

void TransformationManager::pushTranslation(double x, double y, double z) {
    transformStack.push(Transformations::createTranslationMatrix(x, y, z));
    pushInverseTranslation(x, y, z);
}

void TransformationManager::pushScale(double x, double y, double z) {
    transformStack.push(Transformations::createScalingMatrix(x, y, z));
    pushInverseScale(x, y, z);
}

void TransformationManager::pushRotatePointX(double angle) {

    transformStack.push(Transformations::createRotationMatrixX(angle));
    pushInverseRotatePointX(angle);
}

void TransformationManager::pushRotatePointY(double angle) {

    transformStack.push(Transformations::createRotationMatrixY(angle));

    pushInverseRotatePointY(angle);
}

void TransformationManager::pushRotatePointZ(double angle) {

    transformStack.push(Transformations::createRotationMatrixZ(angle));
    pushInverseRotatePointZ(angle);
}

void TransformationManager::pushInverseTranslation(double x, double y, double z) {

    invTransformStack.push(InverseTransformations::createInverseTranslationMatrix(x, y, z));
}

void TransformationManager::pushInverseScale(double x, double y, double z) {

    invTransformStack.push(InverseTransformations::createInverseScalingMatrix(x, y, z));

}

void TransformationManager::pushInverseRotatePointX(double angle) {

    invTransformStack.push(InverseTransformations::createInverseRotationMatrixX(angle));

}

void TransformationManager::pushInverseRotatePointY(double angle) {


    invTransformStack.push(InverseTransformations::createInverseRotationMatrixY(angle));

}

void TransformationManager::pushInverseRotatePointZ(double angle) {

    invTransformStack.push(InverseTransformations::createInverseRotationMatrixZ(angle));

}


std::pair<Eigen::Matrix4d, Eigen::Matrix4d> TransformationManager::getTotalTransformation() {

    if (transformStack.empty()) {
        return {Eigen::Matrix4d::Identity(), Eigen::Matrix4d::Identity()};
    }

    Eigen::Matrix4d totalTransform = transformStack.top();
    //std::cout << totalTransform << "\n" << "\n" << std::endl;
    transformStack.pop();

    while (!transformStack.empty()) {
        totalTransform = transformStack.top() * totalTransform;
        //std::cout << totalTransform << "\n" << "\n" << std::endl;
        transformStack.pop();
    }


    Eigen::Matrix4d totalInvTransform = invTransformStack.top();
    //std::cout << totalInvTransform << "\n" << "\n" << std::endl;
    invTransformStack.pop();

    while (!invTransformStack.empty()) {
        totalInvTransform =  totalInvTransform * invTransformStack.top();
        //std::cout << totalInvTransform << "\n" << "\n" << std::endl;
        invTransformStack.pop();
    }

    std::pair<Eigen::Matrix4d, Eigen::Matrix4d> pair(totalTransform, totalInvTransform);

    return pair;
}
