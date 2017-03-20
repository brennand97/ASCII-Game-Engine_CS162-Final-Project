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

    // Top Wall
    double * t_w_l = douglas::vector::vector(-(unit_width / 2.0), unit_height - 1.0);
    double * t_w_r = douglas::vector::vector(unit_width + (unit_width / 2.0), unit_height - 1.0);
    top_wall = new Wall(t_w_l, t_w_r);
    top_wall->setDrawChar('_');
    physics->addChild(top_wall);
    delete [] t_w_l;
    delete [] t_w_r;

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

    // Set up movable walls
    mvs = new ParticleContainer();
    physics->addChild(mvs);

    double * mv1_1 = douglas::vector::vector(unit_width - 20.0, unit_height - 5.0);
    double * mv1_2 = douglas::vector::vector(unit_width - 5.0, unit_height - 30.0);
    mv1 = new MovableWall(mv1_1, mv1_2, true);
    mvs->addChild(mv1);
    delete [] mv1_1;
    delete [] mv1_2;

    double * mv2_1 = douglas::vector::vector(unit_width / 6.0, unit_height - 10.0);
    double * mv2_2 = douglas::vector::vector(unit_width / 5.0, unit_height / 2.0);
    mv2 = new MovableWall(mv2_1, mv2_2, true);
    mvs->addChild(mv2);
    delete [] mv2_1;
    delete [] mv2_2;

    double * mv3_1 = douglas::vector::vector(unit_width / 2.0, unit_height / 10.0);
    double * mv3_2 = douglas::vector::vector(unit_width / 3.0, unit_height / 4.0);
    mv3 = new MovableWall(mv3_1, mv3_2, true);
    mvs->addChild(mv3);
    delete [] mv3_1;
    delete [] mv3_2;

    mvs_drag = new DragConstraint(0.5);
    mvs->addSubGlobalConstraint(mvs_drag);

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