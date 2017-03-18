//
// Created by Brennan on 3/17/2017.
//

#include "henge_constraint.hpp"
#include "../../personal_utilities/vec_func.hpp"
#include "cmath"

std::string HengeConstraint::TYPE = "henge_constraint";

HengeConstraint::HengeConstraint(double length, double *point) {
    addType(HengeConstraint::TYPE);
    this->length = length;
    this->henge_point = douglas::vector::copy(point);
}

HengeConstraint::~HengeConstraint() {
    delete henge_point;
}

void HengeConstraint::fix(int iter, Particle *p1) {
    double * p2 = henge_point;

    double dx = p2[0] - (*p1)[0];
    double dy = p2[1] - (*p1)[1];

    double dlength = std::sqrt((dx * dx) + (dy * dy));

    double diff = (dlength - length) / dlength;

    (*p1)[0] += dx * diff;
    (*p1)[1] += dy * diff;
}