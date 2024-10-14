//
// Created by berka on 14/10/2024.
//

#include "Geometry/include/unitGeometricObjects/creation/TransformationManager.h"
#include "Math/include/Transformations.h"
#include "Math/include/InverseTransformations.h"

TransformationManager::TransformationManager() {

}

void TransformationManager::pushTranslation(double x, double y, double z) {
    if (!isInverse.has_value()) {
        isInverse = false;
    }

    if (!isInverse.value()) {
        transformStack.push(Transformations::createTranslationMatrix(x, y, z));
    } else {
        throw std::runtime_error("The Manager is in Inverse Mode. Call getTotalTransformation() to reset.");
    }

}

void TransformationManager::pushScale(double x, double y, double z) {
    if (!isInverse.has_value()) {
        isInverse = false;
    }

    if (!isInverse.value()) {
        transformStack.push(Transformations::createScalingMatrix(x, y, z));
    } else {
        throw std::runtime_error("The Manager is in Inverse Mode. Call getTotalTransformation() to reset.");
    }
}

void TransformationManager::pushRotatePointX(double angle) {
    if (!isInverse.has_value()) {
        isInverse = false;
    }

    if (!isInverse.value()) {
        transformStack.push(Transformations::createRotationMatrixX(angle));
    } else {
        throw std::runtime_error("The Manager is in Inverse Mode. Call getTotalTransformation() to reset.");
    }
}

void TransformationManager::pushRotatePointY(double angle) {
    if (!isInverse.has_value()) {
        isInverse = false;
    }

    if (!isInverse.value()) {
        transformStack.push(Transformations::createRotationMatrixY(angle));
    } else {
        throw std::runtime_error("The Manager is in Inverse Mode. Call getTotalTransformation() to reset.");
    }
}

void TransformationManager::pushRotatePointZ(double angle) {
    if (!isInverse.has_value()) {
        isInverse = false;
    }

    if (!isInverse.value()) {
        transformStack.push(Transformations::createRotationMatrixZ(angle));
    } else {
        throw std::runtime_error("The Manager is in Inverse Mode. Call getTotalTransformation() to reset.");
    }
}

void TransformationManager::pushInverseTranslation(double x, double y, double z) {
    if (!isInverse.has_value()) {
        isInverse = true;
    }

    if (!isInverse.value()) {
        transformStack.push(InverseTransformations::createInverseTranslationMatrix(x, y, z));
    } else {
        throw std::runtime_error("The Manager is in Inverse Mode. Call getTotalTransformation() to reset.");
    }
}

void TransformationManager::pushInverseScale(double x, double y, double z) {
    if (!isInverse.has_value()) {
        isInverse = true;
    }

    if (!isInverse.value()) {
        transformStack.push(InverseTransformations::createInverseScalingMatrix(x, y, z));
    } else {
        throw std::runtime_error("The Manager is in Inverse Mode. Call getTotalTransformation() to reset.");
    }
}

void TransformationManager::pushInverseRotatePointX(double angle) {
    if (!isInverse.has_value()) {
        isInverse = true;
    }

    if (!isInverse.value()) {
        transformStack.push(InverseTransformations::createInverseRotationMatrixX(angle));
    } else {
        throw std::runtime_error("The Manager is in Inverse Mode. Call getTotalTransformation() to reset.");
    }
}

void TransformationManager::pushInverseRotatePointY(double angle) {
    if (!isInverse.has_value()) {
        isInverse = true;
    }

    if (!isInverse.value()) {
        transformStack.push(InverseTransformations::createInverseRotationMatrixY(angle));
    } else {
        throw std::runtime_error("The Manager is in Inverse Mode. Call getTotalTransformation() to reset.");
    }
}

void TransformationManager::pushInverseRotatePointZ(double angle) {
    if (!isInverse.has_value()) {
        isInverse = true;
    }

    if (!isInverse.value()) {
        transformStack.push(InverseTransformations::createInverseRotationMatrixZ(angle));
    } else {
        throw std::runtime_error("The Manager is in Inverse Mode. Call getTotalTransformation() to reset.");
    }
}


Eigen::Matrix<double, 4, 4> TransformationManager::getTotalTransformation() {

    Eigen::Matrix<double, 4, 4> totalTransform = Eigen::Matrix<double, 4, 4>::Identity();
    while (!transformStack.empty()) {
        totalTransform = transformStack.top() * totalTransform;
        transformStack.pop();
    }

    isInverse.reset();

    return totalTransform;
}
