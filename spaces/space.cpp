//
// Created by Brennan on 3/6/2017.
//

#include "space.hpp"
#include <string>

std::string Space::TYPE = "space";

Space::Space(int p_w, int p_h) : GameObject() {
    types.push_back(Space::TYPE);
    pixel_width = p_w;
    pixel_height = p_h;
    unit_width = p_w;
    unit_height = p_h;
    physics = new ParticleContainer();
    physics->setParent(this);
}

Space::Space(int p_w, int p_h, double u_w, double u_h) : GameObject() {
    types.push_back(Space::TYPE);
    pixel_width = p_w;
    pixel_height = p_h;
    unit_width = u_w;
    unit_height = u_h;
    physics = new ParticleContainer();
    physics->setParent(this);
}