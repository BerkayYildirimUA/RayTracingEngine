//
// Created by berka on 02/11/2024.
//

#include "RayTracer.h"
#include "thread"
#include <memory>
#include <future>
#include "iostream"
#include <chrono>
#include <thread>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>

void RayTracer::render(Scene &scn, Camera *camera, int blockSize) {

    int nColumns = camera->getScreenWidth() / blockSize;
    int nRows = camera->getScreenHight() / blockSize;
    int numThreads = std::min(nRows, static_cast<int>(std::thread::hardware_concurrency()));

    if (numThreads == 0) {
        numThreads = 1;
    }

    numThreads = 1; // todo debug

    std::vector<std::vector<Color3>> pixelColors(nRows, std::vector<Color3>(nColumns));
    std::mutex colorMutex;

    auto processRows = [&](int startRow, int endRow) {
        Ray threadRay;
        threadRay.setStart(camera->getEye());

        Vector3 dir;
        Vector3 distanceVector(camera->getNormalDistanceVector().vector * camera->getDistance());

        for (int row = startRow; row < endRow; row++) {
            for (int col = 0; col < nColumns; col++) {

                Color3 clr = {0, 0, 0};

                if (row > 140 && row < 990 && col > 460 && col < 680 || true){
                    clr.set(antiAlsiasing(scn, camera, nColumns, nRows, threadRay, dir, distanceVector, row, col));
                    //clr.set(noAntiAlsiasing(scn, camera, nColumns, nRows, threadRay, dir, distanceVector, row, col));

                }


                pixelColors[row][col] = clr;
            }
        }
    };

    // Launch threads, each handling a portion of rows
    std::vector<std::thread> threads;
    threads.reserve(numThreads);
    int rowsPerThread = nRows / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? nRows : (i + 1) * rowsPerThread;  // Last thread may handle extra rows
        threads.emplace_back(processRows, startRow, endRow);
    }

    // Wait for all threads to finish
    for (auto &thread: threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, camera->getScreenWidth(), 0, camera->getScreenHight(), -1, 1);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    for (int row = 0; row < nRows; row++) {
        int flippedRow = nRows - row - 1;
        for (int col = 0; col < nColumns; col++) {
            Color3 &clr = pixelColors[row][col];
            glColor3f(clr.getRed() / (1 + clr.getRed()), clr.getGreen() / (1 + clr.getGreen()),
                      clr.getBlue() / (1 + clr.getBlue())); // rainhard tone mapping: https://64.github.io/tonemapping/
            glRecti(col * blockSize, flippedRow * blockSize, (col + 1) * blockSize, (flippedRow + 1) * blockSize);
        }
    }

}


Color3 RayTracer::noAntiAlsiasing(Scene &scn, const Camera *camera, int nColumns, int nRows, Ray &threadRay,
                                  Vector3 &dir, const Vector3 &distanceVector, double row, double col) {
    double rightVectorAmplitude = (camera->getScreenWidth() / 2.0) * ((2.0 * col / nColumns) - 1.0);
    double upVectorAmplitude = (camera->getScreenHight() / 2.0) * ((2.0 * row / nRows) - 1.0);

    Eigen::Vector4d dir_vector =
            -distanceVector.vector + rightVectorAmplitude * camera->getNormalRightVector().vector +
            upVectorAmplitude * camera->getNormalUpVector().vector;

    dir.vector = std::move(dir_vector);
    threadRay.setDir(std::move(dir));
    Color3 clr = shade(threadRay, scn);
    return clr;
}

Color3 RayTracer::antiAlsiasing(Scene &scn, const Camera *camera, int nColumns, int nRows, Ray &threadRay,
                                Vector3 &dir, const Vector3 &distanceVector, int row, int col) {

    const double THRESHOLD = 10;
    const int MAX_LOOPS = 9;
    int loop = 0;


    double offsetX = 0, offsetY = 0;
    bool needsSubdivision = false;

    double quadrantSize = 1.0;
    std::vector<Color3> colorOfCurrentArea(4);
    std::vector<Color3> averageColorPerLayer;
    averageColorPerLayer.reserve(MAX_LOOPS);


    auto sampleColor = [&](double rowOffset, double colOffset) {
        return this->noAntiAlsiasing(scn, camera, nColumns, nRows, threadRay, dir, distanceVector, row + rowOffset,
                                     col + colOffset);
    };

    do {
        double halfSize = quadrantSize / 2.0;


        colorOfCurrentArea[0] = sampleColor(offsetX, offsetY);
        colorOfCurrentArea[1] = sampleColor(offsetX + halfSize, offsetY);
        colorOfCurrentArea[2] = sampleColor(offsetX, offsetY + halfSize);
        colorOfCurrentArea[3] = sampleColor(offsetX + halfSize, offsetY + halfSize);


        Color3 layerAvrage = (colorOfCurrentArea[0] + colorOfCurrentArea[1] + colorOfCurrentArea[2] + colorOfCurrentArea[3]) / 4.0;


        needsSubdivision = false;
        for (int i = 0; i < 4; ++i) {
            if (colorOfCurrentArea[i].difference(layerAvrage) > THRESHOLD) {
                needsSubdivision = true;
                offsetX += (i % 2) * halfSize;
                offsetY += (i / 2.0) * halfSize;
                break;
            }
        }

        if (needsSubdivision && loop < MAX_LOOPS) {
            loop++;
            quadrantSize = halfSize;
        }

        averageColorPerLayer.push_back(layerAvrage);

    } while (needsSubdivision && loop < MAX_LOOPS);

    Color3 finalColor(0, 0, 0);

    int i = 0;
    for (const Color3& color : averageColorPerLayer) {
        finalColor.add(color/(i+1));
        i++;
    }

    return finalColor;

}

Color3 RayTracer::shade(const Ray &ray, Scene &scn) {
    Intersection best;
    getFirstHit(ray, best, scn);

    if (best.numHits == 0) {
        return {0, 0, 0};
    }

    Ray feeler;
    Eigen::Vector4d hitPoint = best.getHits(0)->hitObject->getTransform() * best.getHits(0)->hitPoint.point;
    feeler.setStart(Point3(hitPoint - 0.001 * ray.dir.vector.normalized()));


    auto tempLight = scn.getListOfLightsSourcePointers()[0];
    Color3 color = shader->getAmbientPart(tempLight, best.getHits(0)->hitObject->material);
    for (const auto &lightSource: scn.getListOfLightsSourcePointers()) {
        Eigen::Vector4d lightPos = lightSource->location.point;
        feeler.setDir(Vector3(lightPos - hitPoint));

        if (this->isInShadow(feeler, scn)) {
            continue;
        }

        color = color + shader->shade(ray, best, lightSource, best.getHits(0)->hitObject->material);
    }

    return color;
}

void RayTracer::getFirstHit(const Ray &ray, Intersection &best, Scene &scn) {
    Intersection inter;
    best.numHits = 0;

    for (auto &listOfObjectPointer: scn.getListOfObjectPointers()) {
        if (!listOfObjectPointer->hit(ray, inter)) {
            continue;
        }

        if (best.numHits == 0 || inter.getHits(0)->hitTime < best.getHits(0)->hitTime) {
            best.set(inter);
        }
    }
}

bool RayTracer::isInShadow(const Ray &ray, Scene &scn) {
    return std::any_of(scn.getListOfObjectPointers().cbegin(), scn.getListOfObjectPointers().cend(),
                       [&ray](const auto &pointer) { return pointer->hit(ray); });
}

const std::unique_ptr<AbstractShader> &RayTracer::getShader() const {
    return shader;
}
