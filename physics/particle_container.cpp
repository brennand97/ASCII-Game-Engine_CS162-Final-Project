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
    addType(ParticleContainer::TYPE);
}

ParticleContainer::~ParticleContainer() {

    std::vector<Constraint*>::iterator c_it;
    for( c_it = specific_constraints.begin(); c_it != specific_constraints.end(); c_it++ ) {
        delete (*c_it);
    }

    std::vector<SingleConstraint*>::iterator sc_it;
    for( sc_it = specific_constraints.begin(); sc_it != specific_constraints.end(); sc_it++ ) {
        delete (*sc_it);
    }

}

void ParticleContainer::addSpecificConstraint(Constraint * p) {
    specific_constraints.push_back(p);
}

void ParticleContainer::addSubGlobalConstraint(SingleConstraint * p) {
    sub_global_constraints.push_back(p);
}

void ParticleContainer::getGlobalConstraints(std::vector < SingleConstraint * > * vec) {
    for(unsigned int i = 0; i < sub_global_constraints.size(); i++) {
        vec->push_back(sub_global_constraints[i]);
    }
    std::vector<GameObject*> parentPCs;
    parent->getParentsOfType(ParticleContainer::TYPE, &parentPCs);
    for(unsigned int i = 0; i < parentPCs.size(); i++) {
        ((ParticleContainer*) parentPCs[i])->getGlobalConstraints(vec);
    }
}

void ParticleContainer::getSubGlobalConstraints(std::vector < SingleConstraint * > * vec) {
    for(unsigned int i = 0; i < sub_global_constraints.size(); i++) {
        vec->push_back(sub_global_constraints[i]);
    }
}

void ParticleContainer::getSpecificConstraints(std::vector < Constraint * > * vec) {
    for(unsigned int i = 0; i < specific_constraints.size(); i++) {
        vec->push_back(specific_constraints[i]);
    }
}

void ParticleContainer::handleConstraints(int iter) {
    std::vector<Constraint*>::iterator it;
    for(it = specific_constraints.begin(); it != specific_constraints.end(); it++) {
        (*it)->fix(iter);
    }

    // Get particles
    std::vector<GameObject*>::iterator g_it;
    std::vector<GameObject*> particles;
    getChildrenOfType(Particle::TYPE, &particles);

    // Get global constraints
    std::vector<SingleConstraint*>::iterator s_it;
    std::vector<SingleConstraint*> global_constraints;
    getGlobalConstraints(&global_constraints);
    for(s_it = global_constraints.begin(); s_it != global_constraints.end(); s_it++) {
        for(g_it = particles.begin(); g_it != particles.end(); g_it++) {
            (*s_it)->fix(iter, (Particle*) *g_it);
        }
    }
}