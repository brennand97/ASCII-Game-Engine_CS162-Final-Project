/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_r_m.hpp"

// Type declaration
std::string GridRM::TYPE = "grid_right_middle";

// Default constructor
GridRM::GridRM(double u_w, double u_h) : Room(u_w, u_h) {
    // Add type to type list
    addType(GridRM::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridRM::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0);

    double * r_w_t = douglas::vector::vector( unit_width - 0.5, unit_height + (unit_height / 2.0));
    double * r_w_b = douglas::vector::vector( unit_width - 0.5, - (unit_height / 2.0));
    right_wall = new Wall(r_w_t, r_w_b);
    right_wall->setDrawChar('|');
    physics->addChild(right_wall);
    delete [] r_w_t;
    delete [] r_w_b;

}

// Steps through one iteration of the physics
void GridRM::step(double dt) {
    GameObject::step(dt);
    handlePhysics(GridRM::RELAXATION_ROUNDS);
}

// Renders the space
void GridRM::render(Screen *screen) {

    // Renders all the children
    renderChildren(screen);
}