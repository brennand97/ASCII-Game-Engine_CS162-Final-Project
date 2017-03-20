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

    // Top Middle Wall
    double * t_m_w_1 = douglas::vector::vector( 0.0, unit_height - (unit_height / 3.0));
    double * t_m_w_2 = douglas::vector::vector( unit_width - (unit_width / 4.0), unit_height - (unit_height / 3.0));
    top_middle_wall = new Wall(t_m_w_1, t_m_w_2);
    top_middle_wall->setDrawChar('_');
    physics->addChild(top_middle_wall);
    delete [] t_m_w_1;
    delete [] t_m_w_2;

    // Bottom Middle Wall
    double * b_m_w_1 = douglas::vector::vector( 0.0, (unit_height / 3.0));
    double * b_m_w_2 = douglas::vector::vector( unit_width - (unit_width / 4.0), (unit_height / 3.0));
    bottom_middle_wall = new Wall(b_m_w_1, b_m_w_2);
    bottom_middle_wall->setDrawChar('_');
    physics->addChild(bottom_middle_wall);
    delete [] b_m_w_1;
    delete [] b_m_w_2;

    // Left Top Middle Wall
    double * l_t_m_w_1 = douglas::vector::vector( (unit_width / 2.5), unit_height);
    double * l_t_m_w_2 = douglas::vector::vector( (unit_width / 2.5), unit_height - (unit_height / 3.0));
    left_top_middle_wall = new Wall(l_t_m_w_1, l_t_m_w_2);
    left_top_middle_wall->setDrawChar('|');
    physics->addChild(left_top_middle_wall);
    delete [] l_t_m_w_1;
    delete [] l_t_m_w_2;

    // Left Bottom Middle Wall
    double * l_b_m_w_1 = douglas::vector::vector( (unit_width / 2.5), 0.0);
    double * l_b_m_w_2 = douglas::vector::vector( (unit_width / 2.5), (unit_height / 3.0));
    left_bottom_middle_wall = new Wall(l_b_m_w_1, l_b_m_w_2);
    left_bottom_middle_wall->setDrawChar('|');
    physics->addChild(left_bottom_middle_wall);
    delete [] l_b_m_w_1;
    delete [] l_b_m_w_2;

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