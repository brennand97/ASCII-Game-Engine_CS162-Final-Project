/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_r_b.hpp"

// Type declaration
std::string GridRB::TYPE = "grid_right_bottom";

// Default constructor
GridRB::GridRB(double u_w, double u_h) : Room(u_w, u_h) {
    // Add type to type list
    addType(GridRB::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridRB::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0);

    // Bottom Wall
    double * b_w_l = douglas::vector::vector( - (unit_width / 2.0), 0.0);
    double * b_w_r = douglas::vector::vector( unit_width + (unit_width / 2.0), 0.0);
    bottom_wall = new Wall(b_w_l, b_w_r);
    bottom_wall->setDrawChar('_');
    physics->addChild(bottom_wall);
    delete [] b_w_l;
    delete [] b_w_r;

    // Right Wall
    double * r_w_t = douglas::vector::vector( unit_width - 0.5, unit_height + (unit_height / 2.0));
    double * r_w_b = douglas::vector::vector( unit_width - 0.5, - (unit_height / 2.0));
    right_wall = new Wall(r_w_t, r_w_b);
    right_wall->setDrawChar('|');
    physics->addChild(right_wall);
    delete [] r_w_t;
    delete [] r_w_b;

    // Left Top Wall
    double * l_t_w_1 = douglas::vector::vector(0.0, unit_height + (unit_height / 2.0));
    double * l_t_w_2 = douglas::vector::vector(0.0, unit_height - (unit_height / 3.0));
    left_top_wall = new Wall(l_t_w_1, l_t_w_2);
    left_top_wall->setDrawChar('|');
    physics->addChild(left_top_wall);
    delete [] l_t_w_1;
    delete [] l_t_w_2;

    // Left Bottom Wall
    double * l_b_w_1 = douglas::vector::vector(0.0, - (unit_height / 2.0));
    double * l_b_w_2 = douglas::vector::vector(0.0, (unit_height / 3.0));
    left_bottom_wall = new Wall(l_b_w_1, l_b_w_2);
    left_bottom_wall->setDrawChar('|');
    physics->addChild(left_bottom_wall);
    delete [] l_b_w_1;
    delete [] l_b_w_2;

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

    // Tunnel Walls

    // Tunnel Top Left Wall
    double * t_t_l_w_1 = douglas::vector::vector( (unit_width / 2.5), unit_height);
    double * t_t_l_w_2 = douglas::vector::vector( (unit_width / 2.5), unit_height - (unit_height / 3.0));
    tunnel_top_left_wall = new Wall(t_t_l_w_1, t_t_l_w_2);
    tunnel_top_left_wall->setDrawChar('|');
    physics->addChild(tunnel_top_left_wall);
    delete [] t_t_l_w_1;
    delete [] t_t_l_w_2;

    // Tunnel Top Right Wall
    double * t_t_r_w_1 = douglas::vector::vector( unit_width - (unit_width / 2.5), unit_height);
    double * t_t_r_w_2 = douglas::vector::vector( unit_width - (unit_width / 2.5), (unit_height / 3.0));
    tunnel_top_right_wall = new Wall(t_t_r_w_1, t_t_r_w_2);
    tunnel_top_right_wall->setDrawChar('|');
    physics->addChild(tunnel_top_right_wall);
    delete [] t_t_r_w_1;
    delete [] t_t_r_w_2;

    // Tunnel Middle Top Wall
    double * t_m_t_w_1 = douglas::vector::vector( 0.0, unit_height - (unit_height / 3.0));
    double * t_m_t_w_2 = douglas::vector::vector( (unit_width / 2.5), unit_height - (unit_height / 3.0));
    tunnel_middle_top_wall = new Wall(t_m_t_w_1, t_m_t_w_2);
    tunnel_middle_top_wall->setDrawChar('_');
    physics->addChild(tunnel_middle_top_wall);
    delete [] t_m_t_w_1;
    delete [] t_m_t_w_2;

    // Tunnel Middle Bottom Wall
    double * t_m_b_w_1 = douglas::vector::vector( 0.0, (unit_height / 3.0));
    double * t_m_b_w_2 = douglas::vector::vector( unit_width - (unit_width / 2.5), (unit_height / 3.0));
    tunnel_middle_bottom_wall = new Wall(t_m_b_w_1, t_m_b_w_2);
    tunnel_middle_bottom_wall->setDrawChar('_');
    physics->addChild(tunnel_middle_bottom_wall);
    delete [] t_m_b_w_1;
    delete [] t_m_b_w_2;

}

// Steps through one iteration of the physics
void GridRB::step(double dt) {
    GameObject::step(dt);
    handlePhysics(GridRB::RELAXATION_ROUNDS);
}

// Renders the space
void GridRB::render(Screen *screen) {

    // Renders all the children
    renderChildren(screen);
}