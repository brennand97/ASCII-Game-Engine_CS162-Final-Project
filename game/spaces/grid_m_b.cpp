/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_m_b.hpp"

// Type declaration
std::string GridMB::TYPE = "grid_middle_bottom";

// Default constructor
GridMB::GridMB(double u_w, double u_h) : Room(u_w, u_h) {
    // Add type to type list
    addType(GridMB::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridMB::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0.1);

}

// Steps through one iteration of the physics
void GridMB::step(double dt) {
    GameObject::step(dt);
    handlePhysics(GridMB::RELAXATION_ROUNDS);
}

// Renders the space
void GridMB::render(Screen *screen) {

    // Renders all the children
    renderChildren(screen);
}