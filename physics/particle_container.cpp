//
// Created by Brennan on 3/6/2017.
//

#include "particle_container.hpp"
#include "../game_object.hpp"
#include "../space.hpp"
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
    for( sc_it = sub_global_constraints.begin(); sc_it != sub_global_constraints.end(); sc_it++ ) {
        delete (*sc_it);
    }

    for( sc_it = super_global_constraints.begin(); sc_it != super_global_constraints.end(); sc_it++ ) {
        delete (*sc_it);
    }

}

void ParticleContainer::addSpecificConstraint(Constraint * p) {
    specific_constraints.push_back(p);
}

void ParticleContainer::addSubGlobalConstraint(SingleConstraint * p) {
    sub_global_constraints.push_back(p);
    if(parent != nullptr) {
        getGlobalConstraints(nullptr, true, false);
    }
}

void ParticleContainer::addSuperGlobalConstraint(SingleConstraint * p) {
    super_global_constraints.push_back(p);
    if(parent != nullptr) {
        getGlobalConstraints(nullptr, true, false);
        Space* world = (Space*) getWorld();
        world->getPhysics()->getSuperGlobalConstraints(nullptr, true);
    }
}

void ParticleContainer::getGlobalConstraints(std::vector < SingleConstraint * > * vec, bool update_cached, bool supers) {
    if(update_cached) {
        cached_global_constraints.clear();
        for(unsigned int i = 0; i < sub_global_constraints.size(); i++) {
            cached_global_constraints.push_back(sub_global_constraints[i]);
        }
        std::vector<GameObject*> parentPCs;
        parent->getParentsOfType(ParticleContainer::TYPE, &parentPCs);
        for(unsigned int i = 0; i < parentPCs.size(); i++) {
            ((ParticleContainer*) parentPCs[i])->getGlobalConstraints(&cached_global_constraints, false, false);
        }
    }
    if(vec != nullptr) {
        for(unsigned int i = 0; i < cached_global_constraints.size(); i++) {
            vec->push_back(cached_global_constraints[i]);
        }
        if(supers) {
            Space* world = (Space*) getWorld();
            world->getPhysics()->getSuperGlobalConstraints(vec);
        }
    }
}

void ParticleContainer::getSubGlobalConstraints(std::vector < SingleConstraint * > * vec) {
    for(unsigned int i = 0; i < sub_global_constraints.size(); i++) {
        vec->push_back(sub_global_constraints[i]);
    }
}

void ParticleContainer::removeSubGlobalConstraint(int index) {
    sub_global_constraints.erase(sub_global_constraints.begin() + index, sub_global_constraints.begin() + index + 1);
}

void ParticleContainer::getSuperGlobalConstraints(std::vector < SingleConstraint * > * vec, bool update_cached) {
    if(((Space*) getWorld())->getPhysics()->getId() == this->getId()) {
        // This is the physics element of a Space
        if(update_cached) {
            master_cached_global_super_constraints.clear();
            std::vector<GameObject*> allPCs;
            this->getChildrenOfType(ParticleContainer::TYPE, &allPCs);
            for(unsigned int i = 0; i < allPCs.size(); i++) {
                if(((ParticleContainer*) allPCs[i])->getId() != this->getId()) {
                    ((ParticleContainer*) allPCs[i])->getSuperGlobalConstraints(&master_cached_global_super_constraints, false);
                }
            }
        }
        if(vec != nullptr) {
            for(unsigned int i = 0; i < master_cached_global_super_constraints.size(); i++) {
                vec->push_back(master_cached_global_super_constraints[i]);
            }
        }
    } else {
        if(vec != nullptr) {
            for(unsigned int i = 0; i < super_global_constraints.size(); i++) {
                vec->push_back(super_global_constraints[i]);
            }
        }
    }
}

void ParticleContainer::getSpecificConstraints(std::vector < Constraint * > * vec) {
    for(unsigned int i = 0; i < specific_constraints.size(); i++) {
        vec->push_back(specific_constraints[i]);
    }
}

void ParticleContainer::addVelocity(double *vel) {
    std::vector<GameObject*> particles;
    getChildrenOfType(Particle::TYPE, &particles);
    std::vector<GameObject*>::iterator it;
    for(it = particles.begin(); it != particles.end(); it++) {
        (*((Particle*) (*it)))[0] += vel[0];
        (*((Particle*) (*it)))[1] += vel[1];
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
    getImmediateChildrenOfType(Particle::TYPE, &particles);

    // Get global constraints
    std::vector<SingleConstraint*>::iterator s_it;
    std::vector<SingleConstraint*> global_constraints;
    getGlobalConstraints(&global_constraints, true);
    for(s_it = global_constraints.begin(); s_it != global_constraints.end(); s_it++) {
        for(g_it = particles.begin(); g_it != particles.end(); g_it++) {
            (*s_it)->fix(iter, (Particle*) *g_it);
        }
    }
}