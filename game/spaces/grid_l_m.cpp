/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_l_m.hpp"

// Type declaration
std::string GridLM::TYPE = "grid_left_middle";

// Default constructor
GridLM::GridLM(double u_w, double u_h) : Room(u_w, u_h) {
    // Add type to type list
    addType(GridLM::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridLM::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0);

    double * l_w_t = douglas::vector::vector( 0.0, unit_height + (unit_height / 2.0));
    double * l_w_b = douglas::vector::vector( 0.0, - (unit_height / 2.0));
    left_wall = new Wall(l_w_t, l_w_b);
    left_wall->setDrawChar('|');
    physics->addChild(left_wall);
    delete [] l_w_t;
    delete [] l_w_b;

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