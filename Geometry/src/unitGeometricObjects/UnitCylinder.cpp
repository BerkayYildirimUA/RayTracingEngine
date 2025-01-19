//
// Created by berka on 15/01/2025.
//

#include "Geometry/include/unitGeometricObjects/UnitCylinder.h"
#include "HitInfo.h"
#include "memory"
#include "Intersection.h"

bool UnitCylinder::hit(const Ray &incomingRay, Intersection &intersection) const {
    Ray genRay;
    this->transformRayToObjectSpace(incomingRay, genRay);

    //  Solve quadratic
    double A, B, C, d, F;
    d = (this->s - 1) * genRay.dir.getZ();
    F = 1 + (this->s - 1) * genRay.start.getZ();

    A = genRay.dir.getX() * genRay.dir.getX() + genRay.dir.getY() * genRay.dir.getY() - d * d;

    B = genRay.start.getX() * genRay.dir.getX() + genRay.start.getY() * genRay.dir.getY() - F * d;

    C = genRay.start.getX() * genRay.start.getX() + genRay.start.getY() * genRay.start.getY() - F * F;

    std::vector<std::tuple<double, bool, bool>> candidates; // tValue, isBase, isCap

    int numberOfHits = 0;

    double discriminant = B * B - A * C;
    if (discriminant >= 0.0 && std::abs(A) > 1e-12) {
        double sqrtDisc = std::sqrt(discriminant);
        double tSide1 = (-B - sqrtDisc) / A;
        double tSide2 = (-B + sqrtDisc) / A;

        auto checkSide = [&](double t) {
            if (t >= 0.0) {
                Eigen::Vector3d pt = genRay.calcPoint(t);
                if (pt.z() >= 0.0 && pt.z() <= 1.0) {
                    candidates.push_back({t, false, false});
                }
            }
        };

        checkSide(tSide1);
        checkSide(tSide2);
    }

    // Base intersection (z=0)
    double tBase = -genRay.start.getZ() / genRay.dir.getZ();
    if (tBase >= 0.0) {
        Eigen::Vector3d ptBase = genRay.calcPoint(tBase);
        // Radius limit at z=0 is 1.0
        if (ptBase.x() * ptBase.x() + ptBase.y() * ptBase.y() <= 1.0) {
            candidates.push_back({tBase, true, false});
        }
    }

    // Cap intersection (z=1)
    if (std::abs(genRay.dir.getZ()) > 1e-12) {
        double tCap = (1.0 - genRay.start.getZ()) / genRay.dir.getZ();
        if (tCap >= 0.0) {
            Eigen::Vector3d ptCap = genRay.calcPoint(tCap);
            // Radius limit at z=1 is s
            if (ptCap.x() * ptCap.x() + ptCap.y() * ptCap.y() <= s * s) {
                candidates.push_back({tCap, false, true});
            }
        }
    }

    // Remove t <= 0
    candidates.erase(
            std::remove_if(candidates.begin(), candidates.end(),
                           [](auto &c) {
                               return std::get<0>(c) <= 0.0;
                           }
            ),
            candidates.end()
    );

    // Sort t
    std::sort(candidates.begin(), candidates.end(),
              [](auto &a, auto &b) { return std::get<0>(a) < std::get<0>(b); });

    double t1 = -10000;
    double t2 = -10000;

    bool t1IsBase = false;
    bool t1IsCap = false;
    bool t2IsBase = false;
    bool t2IsCap = false;


    Eigen::Vector3d pointT1;
    Eigen::Vector3d pointT2;

    if (!candidates.empty()) {
        t1 = std::get<0>(candidates[0]);
        t1IsBase = std::get<1>(candidates[0]);
        t1IsCap = std::get<2>(candidates[0]);

        if (candidates.size() > 1) {
            t2 = std::get<0>(candidates[1]);
            t2IsBase = std::get<1>(candidates[1]);
            t2IsCap = std::get<2>(candidates[1]);
        }

        pointT1 = genRay.calcPoint(t1);
        pointT2 = genRay.calcPoint(t2);
    } else {
        return false;
    }

    if (t1 >= 1e-12) {
        auto &info = intersection.getHit(0);

        info->hitTime = t1;

        if (t1IsBase) {
            info->surface = 1;
        } else if (t1IsCap) {
            info->surface = 2;
        } else {
            info->surface = 0; // wall
        }

        info->hitObject = std::static_pointer_cast<PrimitiveObjects>(
                const_cast<UnitCylinder *>(this)->shared_from_this()
        );

        info->hitPoint.set(pointT1.x(), pointT1.y(), pointT1.z());

        Vector3 norm;

        if (t1IsBase) {
            norm.set(0, 0, -1);
        } else if (t1IsCap) {
            norm.set(0, 0, 1);
        } else {
            norm.set(pointT1.x(), pointT1.y(), -(this->s - 1) * (1 + (this->s - 1) * pointT1.z()));
        }

        double dp = genRay.dir * norm;
        info->isEntering = (dp < 0.0);
        if (!info->isEntering) {
            norm = -norm;
        }


        info->hitNormal.set(norm);


        numberOfHits = 1;

    }

    if (t2 >= 1e-12 && (std::abs(t1 - t2) >= 1e-12)) {

        auto &info = intersection.getHit(numberOfHits);

        info->hitTime = t2;

        if (t2IsBase) {
            info->surface = 1;
        } else if (t2IsCap) {
            info->surface = 2;
        } else {
            info->surface = 0; // wall
        }

        info->hitObject = std::static_pointer_cast<PrimitiveObjects>(
                const_cast<UnitCylinder *>(this)->shared_from_this()
        );

        info->hitPoint.set(pointT2.x(), pointT2.y(), pointT2.z());

        Vector3 norm;

        if (t2IsBase) {
            norm.set(0, 0, -1);
        } else if (t2IsCap) {
            norm.set(0, 0, 1);
        } else {
            norm.set(pointT2.x(), pointT2.y(), -(this->s - 1) * (1 + (this->s - 1) * pointT2.z()));
        }

        double dp = genRay.dir * norm;
        info->isEntering = (dp < 0.0);
        if (!info->isEntering) {
            norm = -norm;
        }

        info->hitNormal.set(norm);

        numberOfHits++;
    }


    intersection.numHits = numberOfHits;
    return (numberOfHits > 0);
}

bool UnitCylinder::hit(const Ray &incomingRay) const {
    Ray genRay;
    this->transformRayToObjectSpace(incomingRay, genRay);

    //  Solve quadratic
    double A, B, C, d, F;
    d = (this->s - 1) * genRay.dir.getZ();
    F = 1 + (this->s - 1) * genRay.start.getZ();

    A = genRay.dir.getX() * genRay.dir.getX() + genRay.dir.getY() * genRay.dir.getY() - d * d;

    B = genRay.start.getX() * genRay.dir.getX() + genRay.start.getY() * genRay.dir.getY() - F * d;

    C = genRay.start.getX() * genRay.start.getX() + genRay.start.getY() * genRay.start.getY() - F * F;

    double discriminant = B * B - A * C;

    if (discriminant >= 0.0 && std::abs(A) > 1e-12)
    {
        double sqrtDisc = std::sqrt(discriminant);
        double tSide1   = (-B - sqrtDisc) / A;
        double tSide2   = (-B + sqrtDisc) / A;

        auto checkSide = [&](double t) {
            if (t >= 0.0 && t <= 1.0) {
                Eigen::Vector3d pt = genRay.calcPoint(t);
                // Must be within z=0 and z=1 for the frustum side
                if (pt.z() >= 0.0 && pt.z() <= 1.0) {
                    return true; // valid intersection
                }
            }
            return false;
        };

        if (checkSide(tSide1)) return true;
        if (checkSide(tSide2)) return true;

        //checkSide(tSide1);
        //checkSide(tSide2);
    }

    if (std::abs(genRay.dir.getZ()) > 1e-12)
    {
        double tBase = -genRay.start.getZ() / genRay.dir.getZ();
        if (tBase >= 0.0 && tBase <= 1.0) {
            Eigen::Vector3d ptBase = genRay.calcPoint(tBase);
            // Radius limit at base is 1.0
            if (ptBase.x() * ptBase.x() + ptBase.y() * ptBase.y() <= 1.0) {
                return true;
            }
        }
    }

    if (std::abs(genRay.dir.getZ()) > 1e-12)
    {
        double tCap = (1.0 - genRay.start.getZ()) / genRay.dir.getZ();
        if (tCap >= 0.0 && tCap <= 1.0) {
            Eigen::Vector3d ptCap = genRay.calcPoint(tCap);
            // Radius limit at z=1 is s
            if (ptCap.x() * ptCap.x() + ptCap.y() * ptCap.y() <= s * s) {
                return true;
            }
        }
    }
    return false;

}

UnitCylinder::UnitCylinder(const std::shared_ptr<AbstractMaterial> &material, double s) : PrimitiveObjects(
        material) { this->s = s; }

Point3 UnitCylinder::getCenter() {
    return {0, 0, 0.5};
}
