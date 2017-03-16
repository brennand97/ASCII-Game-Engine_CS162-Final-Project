/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_r_t.hpp"

// Type declaration
std::string GridRT::TYPE = "grid_right_top";

// Default constructor
GridRT::GridRT(double u_w, double u_h) : Room(u_w, u_h) {
    // Add type to type list
    addType(GridRT::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridRT::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0.1);

}

// Steps through one iteration of the physics
void GridRT::step(double dt) {
    GameObject::step(dt);
    handlePhysics(GridRT::RELAXATION_ROUNDS);
}

// Renders the space
void GridRT::render(Screen *screen) {

    // Renders all the children
    renderChildren(screen);
}