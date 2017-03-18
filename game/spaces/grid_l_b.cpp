/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_l_b.hpp"

// Type declaration
std::string GridLB::TYPE = "grid_left_bottom";

// Default constructor
GridLB::GridLB(double u_w, double u_h) : Room(u_w, u_h) {
    // Add type to type list
    addType(GridLB::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridLB::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0);

    // Left Wall
    double * l_w_t = douglas::vector::vector( 0.0, unit_height + (unit_height / 2.0));
    double * l_w_b = douglas::vector::vector( 0.0, - (unit_height / 2.0));
    left_wall = new Wall(l_w_t, l_w_b);
    left_wall->setDrawChar('|');
    physics->addChild(left_wall);
    delete [] l_w_t;
    delete [] l_w_b;

    // Bottom Wall
    double * b_w_l = douglas::vector::vector( - (unit_width / 2.0), 0.0);
    double * b_w_r = douglas::vector::vector( unit_width + (unit_width / 2.0), 0.0);
    bottom_wall = new Wall(b_w_l, b_w_r);
    bottom_wall->setDrawChar('_');
    physics->addChild(bottom_wall);
    delete [] b_w_l;
    delete [] b_w_r;

    // Top Left Wall
    double * t_l_w_1 = douglas::vector::vector( -(unit_width / 2.0), unit_height - 1.0);
    double * t_l_w_2 = douglas::vector::vector( (unit_width / 2.5), unit_height - 1.0);
    top_left_wall = new Wall(t_l_w_1, t_l_w_2);
    top_left_wall->setDrawChar('_');
    physics->addChild(top_left_wall);
    delete [] t_l_w_1;
    delete [] t_l_w_2;

    // Top Right Wall
    double * t_r_w_1 = douglas::vector::vector( unit_width + (unit_width / 2.0), unit_height - 1.0);
    double * t_r_w_2 = douglas::vector::vector( unit_width - (unit_width / 2.5), unit_height - 1.0);
    top_right_wall = new Wall(t_r_w_1, t_r_w_2);
    top_right_wall->setDrawChar('_');
    physics->addChild(top_right_wall);
    delete [] t_r_w_1;
    delete [] t_r_w_2;

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

}

// Steps through one iteration of the physics
void GridLB::step(double dt) {
    GameObject::step(dt);
    handlePhysics(GridLB::RELAXATION_ROUNDS);
}

// Renders the space
void GridLB::render(Screen *screen) {

    // Renders all the children
    renderChildren(screen);
}