/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_r_b.hpp"

// Type declaration
std::string GridRB::TYPE = "grid_right_bottom";

// Default constructor
GridRB::GridRB(double u_w, double u_h) : Room(u_w, u_h) {
    // Add type to type list
    addType(GridRB::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridRB::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0.1);

}

// Steps through one iteration of the physics
void GridRB::step(double dt) {
    GameObject::step(dt);
    handlePhysics(GridRB::RELAXATION_ROUNDS);
}

// Renders the space
void GridRB::render(Screen *screen) {

    // Renders all the children
    renderChildren(screen);
}