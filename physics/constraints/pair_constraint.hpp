/**
 * Author:      Brennan Douglas
 * Date:        03/07/2017
 * Description: This is the header file for the PairConstraint class
 */

#ifndef FINAL_PROJECT_PAIR_CONSTRAINT_HPP
#define FINAL_PROJECT_PAIR_CONSTRAINT_HPP

#include "constraint.hpp"
#include <string>

// Defines a constraint that works between two particles.
class PairConstraint : public Constraint {
public:

    static std::string TYPE;

    PairConstraint();

    void fix(int);
    virtual void fix(int, Particle*, Particle*) = 0;
};

#endif //FINAL_PROJECT_PAIR_CONSTRAINT_HPP
