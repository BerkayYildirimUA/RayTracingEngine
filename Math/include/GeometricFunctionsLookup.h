//
// Created by berka on 03/11/2024.
//

#include <vector>
#include <cmath>
#include <mutex>
#include "Eigen/Core"


#ifndef RAYTRACINGENGINE_GEOMETRICFUNCTIONSLOOKUP_H
#define RAYTRACINGENGINE_GEOMETRICFUNCTIONSLOOKUP_H


class GeometricFunctionsLookup {
public:

    GeometricFunctionsLookup() = delete;

    static double getAcos(double x) {
        return std::acos(x);


        //return EIGEN_PI/2 - x - 0.2146 * x*x*x - 0.0890 * x*x*x*x*x - 0.0502 * x * x*x*x * x*x*x;

        //initializeAcosTable();
        //return lookupAcos(x);
    }

    static double getCos(double x) {
        return std::cos(x);

        //return 1 - 0.49999905 * x*x + 0.04166368 * x*x*x*x - 0.00138502 * x*x*x*x*x*x;

        //initializeCosTable();
        //return lookupCos(x);
    }

private:

    static const int ACOS_TABLE_SIZE = 10000;
    static constexpr double MIN_ACOS_X = -1.0;
    static constexpr double MAX_ACOS_X = 1.0;
    static constexpr double ACOS_STEP = (MAX_ACOS_X - MIN_ACOS_X) / (ACOS_TABLE_SIZE - 1);

    static constexpr double COS_STEP = EIGEN_PI / 18000.0;
    static const int COS_TABLE_SIZE = static_cast<int>(2 * EIGEN_PI / COS_STEP) + 1;



    static std::vector<double> acosTable;
    static std::vector<double> cosTable;
    static std::once_flag acosInitFlag;
    static std::once_flag cosInitFlag;


    static void initializeAcosTable() {
        std::call_once(acosInitFlag, [] {
            acosTable.resize(ACOS_TABLE_SIZE);
            for (int i = 0; i < ACOS_TABLE_SIZE; ++i) {
                double x = MIN_ACOS_X + i * ACOS_STEP;
                acosTable[i] = std::acos(x);
            }
        });
    }

    static void initializeCosTable() {
        std::call_once(cosInitFlag, [] {
            cosTable.resize(COS_TABLE_SIZE);
            for (int i = 0; i < COS_TABLE_SIZE; ++i) {
                double angle = i * COS_STEP;
                cosTable[i] = std::cos(angle);
            }
        });
    }

    static double lookupAcos(double x) {
        if (x < MIN_ACOS_X) {
            x = MIN_ACOS_X;
        }

        if (x > MAX_ACOS_X) {
            x = MAX_ACOS_X;
        }

        double position = (x - MIN_ACOS_X) / ACOS_STEP;
        int index = static_cast<int>(position);
        double fraction = position - index;

        if (index >= ACOS_TABLE_SIZE - 1) {
            return acosTable[ACOS_TABLE_SIZE - 1];
        }

        double lowerValue = acosTable[index];
        double upperValue = acosTable[index + 1];
        return lowerValue + fraction * (upperValue - lowerValue);
    }

    static double lookupCos(double angle) {
        // Normalize angle to [0, 2π]
        angle = std::fmod(angle, 2 * EIGEN_PI);
        if (angle < 0) angle += 2 * EIGEN_PI;

        double position = angle / COS_STEP;
        int index = static_cast<int>(position) % COS_TABLE_SIZE;
        double fraction = position - index;

        if (index >= COS_TABLE_SIZE - 1) return cosTable[COS_TABLE_SIZE - 1];

        double lowerValue = cosTable[index];
        double upperValue = cosTable[(index + 1) % COS_TABLE_SIZE];
        return lowerValue + fraction * (upperValue - lowerValue);
    }


};



#endif //RAYTRACINGENGINE_GEOMETRICFUNCTIONSLOOKUP_H
