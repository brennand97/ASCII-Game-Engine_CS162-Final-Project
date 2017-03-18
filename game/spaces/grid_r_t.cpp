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
    boundary->setRigid(0);

    double * t_w_l = douglas::vector::vector(-(unit_width / 2.0), unit_height - 1.0);
    double * t_w_r = douglas::vector::vector(unit_width + (unit_width / 2.0), unit_height - 1.0);
    top_wall = new Wall(t_w_l, t_w_r);
    top_wall->setDrawChar('_');
    physics->addChild(top_wall);
    delete [] t_w_l;
    delete [] t_w_r;

    double * r_w_t = douglas::vector::vector( unit_width - 0.5, unit_height + (unit_height / 2.0));
    double * r_w_b = douglas::vector::vector( unit_width - 0.5, - (unit_height / 2.0));
    right_wall = new Wall(r_w_t, r_w_b);
    right_wall->setDrawChar('|');
    physics->addChild(right_wall);
    delete [] r_w_t;
    delete [] r_w_b;

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