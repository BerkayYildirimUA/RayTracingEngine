//
// Created by berka on 03/11/2024.
//

#include "GeometricFunctionsLookup.h"


std::vector<double> GeometricFunctionsLookup::acosTable;
std::vector<double> GeometricFunctionsLookup::cosTable;
std::once_flag GeometricFunctionsLookup::acosInitFlag;
std::once_flag GeometricFunctionsLookup::cosInitFlag;