/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_l_t.hpp"

// Type declaration
std::string GridLT::TYPE = "grid_left_top";

// Default constructor
GridLT::GridLT(double u_w, double u_h) : Room(u_w, u_h) {
    // Add type to type list
    addType(GridLT::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridLT::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0.1);

}

// Steps through one iteration of the physics
void GridLT::step(double dt) {
    GameObject::step(dt);
    handlePhysics(GridLT::RELAXATION_ROUNDS);
}

// Renders the space
void GridLT::render(Screen *screen) {

    // Renders all the children
    renderChildren(screen);
}