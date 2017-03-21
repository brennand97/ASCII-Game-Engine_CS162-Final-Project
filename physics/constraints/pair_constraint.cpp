/**
 * Author:      Brennan Douglas
 * Date:        03/07/2017
 * Description: This is the source file for the PairConstraint class
 */

#include "pair_constraint.hpp"
#include <string>
#include <stdexcept>

std::string PairConstraint::TYPE = "pair_constraint";

// Basic constructor for PairConstraint
PairConstraint::PairConstraint() : Constraint() {
    addType(PairConstraint::TYPE);
}

// Calls on all stored particles appropriately for pair functionality
void PairConstraint::fix(int iter) {
    if(particles.size() % 2 != 0) {
        throw std::invalid_argument("There are not an even number of particles, there is an incomplete particle pair.");
    } else {
        for(unsigned int i = 0; i < particles.size(); i+=2) {
            if(i + 1 < particles.size() && particles[i] != nullptr && particles[i+1] != nullptr) {
                fix(iter, particles[i], particles[i+1]);
            }
        }
    }
}