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
    boundary->setRigid(0);

    // Top Wall
    double * t_w_l = douglas::vector::vector(-(unit_width / 2.0), unit_height - 1.0);
    double * t_w_r = douglas::vector::vector(unit_width + (unit_width / 2.0), unit_height - 1.0);
    top_wall = new Wall(t_w_l, t_w_r);
    top_wall->setDrawChar('_');
    physics->addChild(top_wall);
    delete [] t_w_l;
    delete [] t_w_r;

    // Left Wall
    double * l_w_t = douglas::vector::vector( 0.0, unit_height + (unit_height / 2.0));
    double * l_w_b = douglas::vector::vector( 0.0, - (unit_height / 2.0));
    left_wall = new Wall(l_w_t, l_w_b);
    left_wall->setDrawChar('|');
    physics->addChild(left_wall);
    delete [] l_w_t;
    delete [] l_w_b;

    // Right Top Wall
    double * r_t_w_1 = douglas::vector::vector(unit_width - 0.5, unit_height + (unit_height / 2.0));
    double * r_t_w_2 = douglas::vector::vector(unit_width - 0.5, unit_height - (unit_height / 3.0));
    right_top_wall = new Wall(r_t_w_1, r_t_w_2);
    right_top_wall->setDrawChar('|');
    physics->addChild(right_top_wall);
    delete [] r_t_w_1;
    delete [] r_t_w_2;

    // Right Bottom Wall
    double * r_b_w_1 = douglas::vector::vector(unit_width - 0.5, - (unit_height / 2.0));
    double * r_b_w_2 = douglas::vector::vector(unit_width - 0.5, (unit_height / 3.0));
    right_bottom_wall = new Wall(r_b_w_1, r_b_w_2);
    right_bottom_wall->setDrawChar('|');
    physics->addChild(right_bottom_wall);
    delete [] r_b_w_1;
    delete [] r_b_w_2;

    // Bottom Left Wall
    double * b_l_w_1 = douglas::vector::vector( -(unit_width / 2.0), 0.0);
    double * b_l_w_2 = douglas::vector::vector( (unit_width / 2.5), 0.0);
    bottom_left_wall = new Wall(b_l_w_1, b_l_w_2);
    bottom_left_wall->setDrawChar('_');
    physics->addChild(bottom_left_wall);
    delete [] b_l_w_1;
    delete [] b_l_w_2;

    // Bottom Right Wall
    double * b_r_w_1 = douglas::vector::vector( unit_width + (unit_width / 2.0), 0.0);
    double * b_r_w_2 = douglas::vector::vector( unit_width - (unit_width / 2.5), 0.0);
    bottom_right_wall = new Wall(b_r_w_1, b_r_w_2);
    bottom_right_wall->setDrawChar('_');
    physics->addChild(bottom_right_wall);
    delete [] b_r_w_1;
    delete [] b_r_w_2;

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