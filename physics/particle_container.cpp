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
    type = ParticleContainer::TYPE;
}

void ParticleContainer::getGlobalConstraints(std::vector<Constraint*> * vec) {
    for(unsigned int i = 0; i < sub_global_constraints.size(); i++) {
        vec->push_back(sub_global_constraints[i]);
    }
    std::vector<GameObject*> parentPCs;
    parent->getParentsOfType(ParticleContainer::TYPE, &parentPCs);
    for(unsigned int i = 0; i < parentPCs.size(); i++) {
        ((ParticleContainer*) parentPCs[i])->getGlobalConstraints(vec);
    }
}

void ParticleContainer::step(double dt) {

}

void ParticleContainer::render() {

}