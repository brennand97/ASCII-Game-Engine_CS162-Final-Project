//
// Created by Brennan on 3/6/2017.
//

#include "constraint.hpp"
#include <string>

std::string Constraint::TYPE = "constraint";

void Constraint::removeParticle(unsigned int id) {
    std::vector<GameObject*>::iterator it;
    for(unsigned int i = 0; i < particles.size(); i++) {
        if (particles[i]->getId() == id) {
            particles.erase(particles.begin() + i, particles.begin() + i + 1);
            return;
        }
    }
}

void Constraint::exclude(GameObject *go) {
    if(!isExcluded(go)) {
        excluded.push_back(go->getId());
    }
}

bool Constraint::isExcluded(GameObject *go) {
    for(unsigned int i = 0; i < excluded.size(); i++) {
        unsigned int id = excluded[i];
        if(go->getId() == id) {
            return true;
        }
    }
    if(go->getParent() != nullptr) {
        return isExcluded(go->getParent());
    } else {
        return false;
    }
}