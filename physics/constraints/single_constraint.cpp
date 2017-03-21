/**
 * Author:      Brennan Douglas
 * Date:        03/07/2017
 * Description: This is the header file for the SingleConstraint class
 */

#include "single_constraint.hpp"
#include <string>

std::string SingleConstraint::TYPE = "single_constraint";

// Basic constructor for SingleConstraint
SingleConstraint::SingleConstraint() : Constraint() {
    addType(SingleConstraint::TYPE);
}

// Method that applies constraint to all stored items one at a time
void SingleConstraint::fix(int iter) {
    for(unsigned int i = 0; i < particles.size(); i++) {
        if(particles[i] != nullptr) {
            fix(iter, particles[i]);
        }
    }
}