/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_l_b.hpp"

// Type declaration
std::string GridLB::TYPE = "grid_left_bottom";

// Default constructor
GridLB::GridLB(double u_w, double u_h) : Room(u_w, u_h) {
    // Add type to type list
    addType(GridLB::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridLB::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0.1);

}

// Steps through one iteration of the physics
void GridLB::step(double dt) {
    GameObject::step(dt);
    handlePhysics(GridLB::RELAXATION_ROUNDS);
}

// Renders the space
void GridLB::render(Screen *screen) {

    // Renders all the children
    renderChildren(screen);
}