//
// Created by Brennan on 3/6/2017.
//

#include "space.hpp"
#include "../physics/constraints/box_constraint.hpp"
#include <iostream>
#include <string>
#include <algorithm>

std::string Space::TYPE = "space";

Space::Space(int p_w, int p_h) : Space(p_w, p_h, p_w, p_h) {}

Space::Space(int p_w, int p_h, double u_w, double u_h) : GameObject() {
    addType(Space::TYPE);
    pixel_width = p_w;
    pixel_height = p_h;
    unit_width = u_w;
    unit_height = u_h;

    screen = new Screen(pixel_width, pixel_height);

    physics = new ParticleContainer();
    physics->setParent(this);
    addChild(physics);

    boundary = new BoxConstraint(0, 0, unit_width - 1, unit_height - 1);
    physics->addSubGlobalConstraint(boundary);
}

Space::~Space() {
    delete screen;
}

void Space::handlePhysics(int t_iter) {

    for(int i = 0; i < t_iter; i++) {

        std::vector<GameObject*> c_pcs;
        getChildrenOfType(ParticleContainer::TYPE, &c_pcs);
        std::vector<GameObject*>::iterator it;
        for(it = c_pcs.begin(); it != c_pcs.end(); it++) {
            ((ParticleContainer*) *it)->handleConstraints( i + 1 );
        }

    }

}

double Space::getXUnitsPerPixel() {
    return unit_width/pixel_width;
}

double Space::getYUnitsPerPixel() {
    return unit_height/pixel_height;
}

double Space::getUnitsPerPixel() {
    return std::min(getXUnitsPerPixel(), getYUnitsPerPixel());
}