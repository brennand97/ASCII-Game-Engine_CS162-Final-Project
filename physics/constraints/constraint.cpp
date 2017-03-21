/**
 * Author:      Brennan Douglas
 * Date:        03/06/2017
 * Description: This is the source file for the Constraint class
 */

#include "constraint.hpp"
#include <string>

std::string Constraint::TYPE = "constraint";

// Remove a particle from the list of particles effected
void Constraint::removeParticle(unsigned int id) {
    std::vector<GameObject*>::iterator it;
    for(unsigned int i = 0; i < particles.size(); i++) {
        if (particles[i]->getId() == id) {
            particles.erase(particles.begin() + i, particles.begin() + i + 1);
            return;
        }
    }
}

// Exclude a GameObject and all its children from the constraint
void Constraint::exclude(GameObject *go) {
    if(!isExcluded(go)) {
        excluded.push_back(go->getId());
    }
}

// Check if a GameObject is excluded from the constraint
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