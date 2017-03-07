//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_LINE_CONSTRAINT_HPP
#define FINAL_PROJECT_LINE_CONSTRAINT_HPP

#include <iostream>
#include "constraint.hpp"
#include <cmath>

class LineConstraint : public Constraint {
private:
    double length;
    Constraint::Equality  eq;
public:
    LineConstraint(double, Constraint::Equality);

    double getLength() { return length; }
    void setLength(double length) { this->length = length; }
    Constraint::Equality getEquality() { return eq; }
    void setEquality(Constraint::Equality eq) { this->eq = eq; }

    void fix();
    void fix(Particle*, Particle*);
};

#endif //FINAL_PROJECT_LINE_CONSTRAINT_HPP
