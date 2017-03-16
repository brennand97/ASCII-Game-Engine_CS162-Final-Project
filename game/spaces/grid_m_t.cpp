/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_m_t.hpp"

// Type declaration
std::string GridMT::TYPE = "grid_middle_top";

// Default constructor
GridMT::GridMT(double u_w, double u_h) : Room(u_w, u_h) {
    // Add type to type list
    addType(GridMT::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridMT::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0.1);

}

// Steps through one iteration of the physics
void GridMT::step(double dt) {
    GameObject::step(dt);
    handlePhysics(GridMT::RELAXATION_ROUNDS);
}

// Renders the space
void GridMT::render(Screen *screen) {

    // Renders all the children
    renderChildren(screen);
}