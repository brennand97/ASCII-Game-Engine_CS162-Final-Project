/**
 * Author:      Brennan Douglas
 * Date:        03/06/2017
 * Description: This is the header file for the Space class
 */

#include "space.hpp"
#include "physics/constraints/box_constraint.hpp"
#include <iostream>
#include <string>
#include <algorithm>

std::string Space::TYPE = "space";

// Space Constructor with unit width and unit height
Space::Space(double u_w, double u_h) : GameObject() {
    addType(Space::TYPE);
    unit_width = u_w;
    unit_height = u_h;

    physics = new ParticleContainer();
    physics->setParent(this);
    addChild(physics);

    boundary = new BoxConstraint(0, 0, unit_width - 1, unit_height - 1, 1);
    physics->addSubGlobalConstraint(boundary);
}

// Default space deconstructor
Space::~Space() {}

// Handle the physics of the simulation
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

// Respond to new child by requesting updating of the physics element's super global constraint master cache
void Space::newChild(GameObject *child) {
    physics->getSuperGlobalConstraints(nullptr, true);
}

// Convert point in units to point in pixels
double* Space::convertToPixels(const double x, const double y, Screen* screen) {
    double x_ppu = screen->getWidth() / unit_width;
    double y_ppu = screen->getHeight() / unit_height;
    double* output = new double[2];
    output[0] = x * x_ppu;
    output[1] = y * y_ppu;
    return output;
}

// Convert point in units to point in pixels
void Space::convertToPixels(double * x, double * y, Screen* screen) {
    double* output = convertToPixels(*x, *y, screen);
    *x = output[0];
    *y = output[1];
    delete [] output;
}

// Convert point in units to point in pixels
void Space::convertToPixels(double *pos, Screen *screen) {
    convertToPixels(&pos[0], &pos[1], screen);
}

// Convert point in units to point in pixels
double* Space::convertToPixels(const double *pos, Screen *screen) {
    return convertToPixels(pos[0], pos[1], screen);
}

// Convert point in units to point in pixels
double* Space::convertToPixels(Particle *p, Screen *screen) {
    return convertToPixels((*p)[0], (*p)[1], screen);
}