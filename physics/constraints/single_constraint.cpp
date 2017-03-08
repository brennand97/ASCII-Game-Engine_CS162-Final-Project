//
// Created by Brennan on 3/7/2017.
//

#include "single_constraint.hpp"
#include <string>

std::string SingleConstraint::TYPE = "single_constraint";

SingleConstraint::SingleConstraint() : Constraint() {
    addType(SingleConstraint::TYPE);
}

void SingleConstraint::fix(int iter) {
    for(unsigned int i = 0; i < particles.size(); i++) {
        if(particles[i] != nullptr) {
            fix(iter, particles[i]);
        }
    }
}