//
// Created by Brennan on 3/7/2017.
//

#ifndef FINAL_PROJECT_PAIR_CONSTRAINT_HPP
#define FINAL_PROJECT_PAIR_CONSTRAINT_HPP

#include "constraint.hpp"
#include <string>

class PairConstraint : public Constraint {
public:

    static std::string TYPE;

    PairConstraint();

    void fix(int);
    virtual void fix(int, Particle*, Particle*) = 0;
};

#endif //FINAL_PROJECT_PAIR_CONSTRAINT_HPP
