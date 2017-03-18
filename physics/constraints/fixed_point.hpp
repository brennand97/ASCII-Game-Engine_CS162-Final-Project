//
// Created by Brennan on 3/18/2017.
//

#ifndef FINAL_PROJECT_FIXED_POINT_HPP
#define FINAL_PROJECT_FIXED_POINT_HPP

#include "single_constraint.hpp"

class FixedPoint : public SingleConstraint {
protected:
    double * point;
public:
    static std::string TYPE;
    FixedPoint(double * point);
    ~FixedPoint();
    void fix(int iter, Particle* particle);
};

#endif //FINAL_PROJECT_FIXED_POINT_HPP
