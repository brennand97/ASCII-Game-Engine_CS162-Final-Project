//
// Created by Brennan on 3/18/2017.
//

#include "fixed_point.hpp"
#include "../../personal_utilities/vec_func.hpp"

std::string FixedPoint::TYPE = "fixed_point";

FixedPoint::FixedPoint(double *point) : SingleConstraint() {
    addType(FixedPoint::TYPE);
    this->point = douglas::vector::copy(point);
}

FixedPoint::~FixedPoint() {
    delete [] point;
}

void FixedPoint::fix(int iter, Particle *particle) {
    particle->setPosition(point);
}