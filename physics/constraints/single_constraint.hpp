/**
 * Author:      Brennan Douglas
 * Date:        03/07/2017
 * Description: This is the header file for the SingleConstraint class
 */

#ifndef FINAL_PROJECT_SINGLE_CONSTRAINT_HPP
#define FINAL_PROJECT_SINGLE_CONSTRAINT_HPP

#include "constraint.hpp"
#include <string>

// Defines a constraint that can work on a single particle
class SingleConstraint : public Constraint {
public:

    SingleConstraint();

    static std::string TYPE;

    void fix(int);
    virtual void fix(int, Particle*) = 0;
};

#endif //FINAL_PROJECT_SINGLE_CONSTRAINT_HPP
