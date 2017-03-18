//
// Created by Brennan on 3/17/2017.
//

#ifndef FINAL_PROJECT_HENGE_CONSTRAINT_HPP
#define FINAL_PROJECT_HENGE_CONSTRAINT_HPP

#include "single_constraint.hpp"

class HengeConstraint : public SingleConstraint {
protected:

    double length;
    double * henge_point;

public:

    static std::string TYPE;

    HengeConstraint(double length, double * point);
    ~HengeConstraint();

    double getLength() { return this->length; }
    void setLength(double l) { this->length = l; }
    const double * getPoint() { return henge_point; }
    void setPoint(double * point) { henge_point[0] = point[0]; henge_point[1] = point[1]; }

    void fix(int iter, Particle* particle);
};

#endif //FINAL_PROJECT_HENGE_CONSTRAINT_HPP
