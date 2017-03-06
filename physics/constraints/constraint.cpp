//
// Created by Brennan on 3/6/2017.
//

#include "constraint.hpp"

void Constraint::removeParticle(unsigned int id) {
    std::vector<GameObject*>::iterator it;
    for(unsigned int i = 0; i < particles.size(); i++) {
        if (particles[i]->getId() == id) {
            particles.erase(particles.begin() + i, particles.begin() + i + 1);
            return;
        }
    }
}

void Constraint::fix() {
    switch (link) {
        case SINGLE: {
            for(unsigned int i = 0; i < particles.size(); i+=2) {
                fix(*particles[i], *particles[i+1]);
            }
        }
        case PAIR: {
            for(unsigned int i = 0; i < particles.size(); i++) {
                for(unsigned int j = i + 1; j < particles.size(); j++) {
                    fix(*particles[i], *particles[j]);
                }
            }
        }
    }
}