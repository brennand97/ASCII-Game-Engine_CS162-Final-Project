//
// Created by Brennan on 3/7/2017.
//

#ifndef FINAL_PROJECT_SINGLE_CONSTRAINT_HPP
#define FINAL_PROJECT_SINGLE_CONSTRAINT_HPP

#include "constraint.hpp"
#include <string>

class SingleConstraint : public Constraint {
public:

    SingleConstraint();

    static std::string TYPE;

    void fix(int);
    virtual void fix(int, Particle*) = 0;
};

#endif //FINAL_PROJECT_SINGLE_CONSTRAINT_HPP
