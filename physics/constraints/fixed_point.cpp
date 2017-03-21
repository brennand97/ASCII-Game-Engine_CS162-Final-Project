/**
 * Author:      Brennan Douglas
 * Date:        03/18/2017
 * Description: This is the header file for the BoxConstraint class
 */

#include "fixed_point.hpp"
#include "../../personal_utilities/vec_func.hpp"

std::string FixedPoint::TYPE = "fixed_point";

// Constructor for FixedPoint class
// <point> vector of the point that all effected particles will be held at
FixedPoint::FixedPoint(double *point) : SingleConstraint() {
    addType(FixedPoint::TYPE);
    this->point = douglas::vector::copy(point);
}

// Deconstructor for FixedPoint to delete point vector
FixedPoint::~FixedPoint() {
    delete [] point;
}

// Method that sets the position of the particle to the specified point
void FixedPoint::fix(int iter, Particle *particle) {
    particle->setPosition(point);
}