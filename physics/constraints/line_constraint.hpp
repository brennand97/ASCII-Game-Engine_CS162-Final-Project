//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_LINE_CONSTRAINT_HPP
#define FINAL_PROJECT_LINE_CONSTRAINT_HPP

#include "pair_constraint.hpp"
#include <string>
#include <cmath>

class LineConstraint : public PairConstraint {
private:
    double length;
    Constraint::Equality  eq;
public:

    static std::string TYPE;

    LineConstraint(double, Constraint::Equality);

    double getLength() { return length; }
    void setLength(double length) { this->length = length; }
    Constraint::Equality getEquality() { return eq; }
    void setEquality(Constraint::Equality eq) { this->eq = eq; }

    void fix(int, Particle*, Particle*);
};

#endif //FINAL_PROJECT_LINE_CONSTRAINT_HPP
