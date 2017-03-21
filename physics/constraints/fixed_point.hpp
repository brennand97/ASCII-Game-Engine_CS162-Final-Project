/**
 * Author:      Brennan Douglas
 * Date:        03/18/2017
 * Description: This is the header file for the FixedPoint class
 */

#ifndef FINAL_PROJECT_FIXED_POINT_HPP
#define FINAL_PROJECT_FIXED_POINT_HPP

#include "single_constraint.hpp"

// The fixed point class keeps all effected particles at a specific point
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
