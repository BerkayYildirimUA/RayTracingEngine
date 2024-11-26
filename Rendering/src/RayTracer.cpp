//
// Created by berka on 02/11/2024.
//

#include "RayTracer.h"
#include "thread"
#include <memory>
#include <future>
#include "iostream"
#include "optional"
#include "DebugFlags.h"

void RayTracer::render(Scene &scn, Camera *camera, int blockSize) {

    int nColumns = camera->getScreenWidth() / blockSize;
    int nRows = camera->getScreenHight() / blockSize;
    int numThreads = std::min(nRows, static_cast<int>(std::thread::hardware_concurrency()));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, camera->getScreenWidth(), 0, camera->getScreenHight(), -1, 1);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    GLuint pbo;
    glGenBuffers(1, &pbo);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, nColumns * nRows * 3 * sizeof(float), nullptr, GL_STREAM_DRAW);

    if (numThreads == 0 && !DebugFlags::getSingleThreadMode()) {
        numThreads = 1;
    }

    float* pboPtr = (float*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
    auto processRows = [&](int startRow, int endRow) {
        Ray threadRay;
        threadRay.setStart(camera->getEye());

        Vector3 dir;
        Vector3 distanceVector(camera->getNormalDistanceVector().vector * camera->getDistance());

        for (int row = startRow; row < endRow; row++) {
            for (int col = 0; col < nColumns; col++) {

                /*Color3 clr = {0, 0, 0};

                if (row > 400 && row < 403 && col > 643 && col < 645){ //                 if (row > 384 && row < 400 && col > 632 && col < 680 ){
                    //clr.set(antiAlsiasing(scn, camera, nColumns, nRows, threadRay, dir, distanceVector, row, col));
                    clr.set(noAntiAlsiasing(scn, camera, nColumns, nRows, threadRay, dir, distanceVector, row, col));
                    std::cout << "pixle done" << std::endl;
                } else {
                    clr.set(0, 255, 0);
                }*/

                Color3 clr = noAntiAlsiasing(scn, camera, nColumns, nRows, threadRay, dir, distanceVector, row, col);

                //Color3 clr = {1, 1, 1};

                int index = (row * nColumns + col) * 3;
                pboPtr[index] = static_cast<float>(clr.getRed());
                pboPtr[index + 1] = static_cast<float>(clr.getGreen());
                pboPtr[index + 2] = static_cast<float>(clr.getBlue());
            }
        }
    };

    std::vector<std::thread> threads;
    threads.reserve(numThreads);
    int rowsPerThread = nRows / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? nRows : (i + 1) * rowsPerThread;
        threads.emplace_back(processRows, startRow, endRow);
    }

    for (auto &thread: threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

    // Step 6: Render the PBO content to the screen
    glRasterPos2i(0, 0);  // Set raster position to the bottom-left corner
    glDrawPixels(camera->getScreenWidth(), camera->getScreenHight(), GL_RGB, GL_FLOAT, 0);

    // Step 7: Clean up
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    glDeleteBuffers(1, &pbo);

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
    Color3 clr = shade(threadRay, scn, 0);
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
    return shade(ray, scn, best);
}

Color3 RayTracer::shade(const Ray &ray, Scene &scn, Intersection &best) {
    getFirstHit(ray, best, scn);

    if (best.numHits == 0) {
        return {0, 0, 0};
    }

    Ray feeler;
    Eigen::Vector4d hitPoint = best.getHit(0)->hitObject->getTransform() * best.getHit(0)->hitPoint.point;
    feeler.setStart(Point3(hitPoint - 0.001 * ray.dir.vector.normalized()));


    auto tempLight = scn.getListOfLightsSourcePointers()[0];

    Color3 color;

    if(!DebugFlags::getTurnOffAmbientColors()){
        color.add(shader->getAmbientPart(tempLight, best.getHit(0)->hitObject->material));
    }


    for (const auto &lightSource: scn.getListOfLightsSourcePointers()) {
        Eigen::Vector4d lightPos = lightSource->location.point;
        feeler.setDir(Vector3(lightPos - hitPoint));

        if (this->isInShadow(feeler, scn) && !DebugFlags::getTurnOffShadows()) {
            continue;
        }

        color = color + shader->shade(ray, best, lightSource, best.getHit(0)->hitObject->material);
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

        if (best.numHits == 0 || inter.getHit(0)->hitTime < best.getHit(0)->hitTime) {
            best.set(inter);
            //inter.resize(2);
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

Color3 RayTracer::shade(const Ray &ray, Scene &scn, int recursionDepth) {
    Intersection best;
    Color3 regularColors = shade(ray, scn, best);

    if (recursionDepth == MAX_RECURSION_DEPTH || best.numHits == 0){
        return regularColors;
    }

    double shininess = best.getHit(0)->hitObject->material->shininess;
    double transparency = best.getHit(0)->hitObject->material->transparency;
    Point3 hitPoint(best.getHit(0)->hitObject->getTransform() * best.getHit(0)->hitPoint.point); //real hitpoint
    //Vector3 hitNormal = best.getHit(0)->hitNormal;

    Vector3 hitNormal;
    hitNormal.set((best.getHit(0)->hitObject->getInverseTransform().topLeftCorner<3, 3>().transpose() * best.getHit(0)->hitNormal.vector.head(3)).normalized()); //real hitnormal



    //Vector3 normilizedRayDir(ray.dir.vector.head(3).normalized());
    const double epsilon = 1e-5;

    if (shininess > 0.0000001 && !DebugFlags::getTurnOffReflection()){
        Ray reflectionRay;

        reflectionRay.setStart(Point3(hitPoint.point.head(3) + epsilon * hitNormal.vector.head(3))); //move a bit like shadow
        //reflectionRay.setDir(normilizedRayDir - 2 * (normilizedRayDir * hitNormal) * hitNormal);
        reflectionRay.setDir(ray.dir - 2 * (ray.dir * hitNormal) * hitNormal);

        reflectionRay.speedOfLightInCurrentMaterial = best.getHit(0)->hitObject->material->speedOfLight;

        regularColors.add( shininess * shade(reflectionRay, scn, recursionDepth + 1)); //need real world ray
    }


    if (transparency > 0.0000001 && !DebugFlags::getTurnOffRefraction()){
        Ray transparencyRay;

        double dotOfNormalAndDir =   ray.dir.vector.head(3).normalized().dot(hitNormal.vector.head(3));
        double indexOfRefraction;
        if (dotOfNormalAndDir < 0) {
            indexOfRefraction = ray.speedOfLightInCurrentMaterial / best.getHit(0)->hitObject->material->speedOfLight;
        } else {
            indexOfRefraction = best.getHit(0)->hitObject->material->speedOfLight / ray.speedOfLightInCurrentMaterial;
            hitNormal = -hitNormal;
            dotOfNormalAndDir = hitNormal * ray.dir;
        }

        //double dotOfNormalAndDir =  hitNormal * normilizedRayDir;

        double cosTheta = 1 - (indexOfRefraction * indexOfRefraction) * (1 - dotOfNormalAndDir * dotOfNormalAndDir);

        //std::cout << cosTheta << std::endl;

        if (cosTheta > 0){

            Eigen::Vector3d slightyInsidePoint = hitPoint.point.head(3) - epsilon * hitNormal.vector.head(3);;

            transparencyRay.setStart(Point3(slightyInsidePoint));
            cosTheta = std::sqrt(cosTheta);

            //transparencyRay.setDir( indexOfRefraction * normilizedRayDir + (indexOfRefraction * dotOfNormalAndDir - cosTheta) * hitNormal);
            transparencyRay.setDir( indexOfRefraction * ray.dir + (indexOfRefraction * dotOfNormalAndDir - cosTheta) * hitNormal);

            transparencyRay.speedOfLightInCurrentMaterial = best.getHit(0)->hitObject->material->speedOfLight;

            regularColors.add( transparency * shade(transparencyRay, scn, recursionDepth + 1));
        } else {
            Ray totalReflectionRay;
            transparencyRay.setStart(Point3(hitPoint.point.head(3) + epsilon * hitNormal.vector.head(3)));
            totalReflectionRay.setDir(ray.dir - 2 * (ray.dir * hitNormal) * hitNormal);

            totalReflectionRay.speedOfLightInCurrentMaterial = ray.speedOfLightInCurrentMaterial;

            regularColors.add(transparency * shade(totalReflectionRay, scn, recursionDepth + 1));
        }


    }

    return regularColors;
}
