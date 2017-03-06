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
                for(int j = 0; j < 2; j++) {
                    while ((i + j) < particles.size() && particles[i + j] == nullptr) {
                        particles.erase(particles.begin() + i + j, particles.begin() + i + j + 1);
                    }
                }
                if(i + 1 < particles.size()) {
                    fix(particles[i], particles[i+1]);
                } else if(i < particles.size()){
                    fix(particles[i], nullptr);
                }
            }
        }
        case PAIR: {
            for(unsigned int i = 0; i < particles.size(); i++) {
                if(particles[i] != nullptr) {
                    for (unsigned int j = i + 1; j < particles.size(); j++) {
                        if (particles[j] != nullptr) {
                            fix(particles[i], particles[j]);
                        }
                    }
                } else {
                    particles.erase(particles.begin() + i, particles.begin() + i + 1);
                    i--;
                }
            }
        }
    }
}