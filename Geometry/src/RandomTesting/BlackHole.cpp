//
// Created by berka on 19/10/2024.
//

#include "Geometry/include/RandomTesting/BlackHole.h"

BlackHole::BlackHole() {}

bool BlackHole::hit(const Ray &incomingRay, Intersection &intersection) {
    const double G = 3.0;  // Gravitational constant (simplified to 1)
    double lightSpeed = 0.01;

    genRay.dir = incomingRay.dir;
    genRay.start = incomingRay.start;

    if (core->hit(genRay, intersection)) {
        return false;  // The ray hit the black hole core, no escape
    }

    if (sphereOfInfluence->hit(genRay, intersection)) {
        for (unsigned int i = 0; i < 100; ++i) {

            // Move the ray inside the affect area
            genRay.start.point += genRay.dir.vector * intersection.getHits(0)->hitTime;

            // Calculate the gravitational influence (acceleration) on the ray
            Vector3 toBlackhole(genRay.start.point.head(3) * -1);
            double distanceSquared = calcNorm(toBlackhole, toBlackhole);  // Squared distance to the black hole

            // Normalize the vector to the black hole's center
            Vector3 directionToBlackhole(toBlackhole.vector.head(3).normalized());

            // Calculate the gravitational acceleration based on the black hole's mass
            float acceleration = G * blackholeMass / distanceSquared;

            // Update the ray's direction due to gravity (this bends the ray)
            genRay.dir.vector += directionToBlackhole.vector * acceleration;

            // Re-normalize the ray direction to prevent it from stretching due to repeated updates
            genRay.dir.vector.normalize();

            genRay.start.point += genRay.dir.vector.head(3) * lightSpeed;

            if (core->hit(genRay, intersection)) {
                return false;  // The ray hit the black hole core, no escape
            }
            sphereOfInfluence->hit(genRay, intersection);
        }
    }

    // genray is the new ray that needs to be tested to see if it hist any objects, so calling Shade::Firsthit would be ideal but idk how
    intersection.secondaryRays.emplace_back(genRay);

    return true;
}
