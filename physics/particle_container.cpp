//
// Created by Brennan on 3/6/2017.
//

#include "particle_container.hpp"
#include "../game_object.hpp"
#include "constraints/constraint.hpp"
#include <string>
#include <vector>

std::string ParticleContainer::TYPE = "particle_container";

ParticleContainer::ParticleContainer() : GameObject() {
    types.push_back(ParticleContainer::TYPE);
}

void ParticleContainer::getGlobalConstraints(std::vector < Constraint * > * vec) {
    for(unsigned int i = 0; i < sub_global_constraints.size(); i++) {
        vec->push_back(sub_global_constraints[i]);
    }
    std::vector<GameObject*> parentPCs;
    parent->getParentsOfType(ParticleContainer::TYPE, &parentPCs);
    for(unsigned int i = 0; i < parentPCs.size(); i++) {
        ((ParticleContainer*) parentPCs[i])->getGlobalConstraints(vec);
    }
}

void ParticleContainer::getSubGlobalConstraints(std::vector < Constraint * > * vec) {
    for(unsigned int i = 0; i < sub_global_constraints.size(); i++) {
        vec->push_back(sub_global_constraints[i]);
    }
}

void ParticleContainer::getSpecificConstraints(std::vector < Constraint * > * vec) {
    for(unsigned int i = 0; i < specific_constraints.size(); i++) {
        vec->push_back(specific_constraints[i]);
    }
}

void ParticleContainer::handleConstraints() {
    std::vector<Constraint*>::iterator it;
    for(it = specific_constraints.begin(); it != specific_constraints.end(); it++) {
        (*it)->fix();
    }
    //std::vector<Constraint*> global_constraints;
    getGlobalConstraints(&global_constraints);
    for(it = global_constraints.begin(); it != global_constraints.end(); it++) {
        // TODO implement global constraints
    }
}