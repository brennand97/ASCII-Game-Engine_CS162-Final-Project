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
    boundary->setRigid(0);

    double * t_w_l = douglas::vector::vector(-(unit_width / 2.0), unit_height - 1.0);
    double * t_w_r = douglas::vector::vector(unit_width + (unit_width / 2.0), unit_height - 1.0);
    top_wall = new Wall(t_w_l, t_w_r);
    top_wall->setDrawChar('_');
    physics->addChild(top_wall);
    delete [] t_w_l;
    delete [] t_w_r;
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