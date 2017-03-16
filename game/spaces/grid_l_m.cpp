/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_l_m.hpp"

// Type declaration
std::string GridLM::TYPE = "grid_left_middle";

// Default constructor
GridLM::GridLM(double u_w, double u_h) : Space(u_w, u_h) {
    // Add type to type list
    addType(GridLM::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridLM::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0.1);

}

// Steps through one iteration of the physics
void GridLM::step(double dt) {
    GameObject::step(dt);
    handlePhysics(GridLM::RELAXATION_ROUNDS);
}

// Renders the space
void GridLM::render(Screen *screen) {

    // Renders all the children
    renderChildren(screen);
}