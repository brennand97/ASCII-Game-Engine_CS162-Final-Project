/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_m_m.hpp"

// Type declaration
std::string GridMM::TYPE = "grid_middle_middle";

// Default constructor
GridMM::GridMM(double u_w, double u_h) : Space(u_w, u_h) {
    // Add type to type list
    addType(GridMM::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridMM::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0.1);

}

// Steps through one iteration of the physics
void GridMM::step(double dt) {
    GameObject::step(dt);
    handlePhysics(GridMM::RELAXATION_ROUNDS);
}

// Renders the space
void GridMM::render(Screen *screen) {

    // Renders all the children
    renderChildren(screen);
}