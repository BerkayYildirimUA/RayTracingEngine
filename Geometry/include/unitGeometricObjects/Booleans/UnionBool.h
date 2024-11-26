//
// Created by berka on 24/11/2024.
//

#ifndef RAYTRACINGENGINE_UNIONBOOL_H
#define RAYTRACINGENGINE_UNIONBOOL_H

#include "Boolean.h"

class UnionBool : Boolean {

    Intersection useOperation(const Intersection &left, const Intersection &right) const override {

        //Intersection result(left.numHits + right.numHits); //maybe use diffrence instead?

        //result.numHits = left.numHits + right.numHits;

        //std::merge(std::make_move_iterator(left.begin()), std::make_move_iterator(left.end()), std::make_move_iterator(right.begin()), std::make_move_iterator(right.end()), std::make_move_iterator(result.begin()));

        //return result;
    }


};



#endif //RAYTRACINGENGINE_UNIONBOOL_H
