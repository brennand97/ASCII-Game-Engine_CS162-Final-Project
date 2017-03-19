/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_m_t.hpp"
#include <cmath>

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

    // Top Wall
    double * t_w_l = douglas::vector::vector(-(unit_width / 2.0), unit_height - 1.0);
    double * t_w_r = douglas::vector::vector(unit_width + (unit_width / 2.0), unit_height - 1.0);
    top_wall = new Wall(t_w_l, t_w_r);
    top_wall->setDrawChar('_');
    physics->addChild(top_wall);
    delete [] t_w_l;
    delete [] t_w_r;

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

    // Pinwheel Puzzle

    // Top Left Corner
    double * pwp_t_l_c_1 = douglas::vector::vector((unit_width / 2.5), unit_height);
    double * pwp_t_l_c_2 = douglas::vector::vector(0.0, unit_height - (unit_height / 3.0));
    top_left_corner = new Wall(pwp_t_l_c_1, pwp_t_l_c_2);
    top_left_corner->setDrawChar('-');
    physics->addChild(top_left_corner);
    delete [] pwp_t_l_c_1;
    delete [] pwp_t_l_c_2;

    // Top Right Corner
    double * pwp_t_r_c_1 = douglas::vector::vector(unit_width - (unit_width / 2.5), unit_height);
    double * pwp_t_r_c_2 = douglas::vector::vector(unit_width, unit_height - (unit_height / 3.0));
    top_right_corner = new Wall(pwp_t_r_c_1, pwp_t_r_c_2);
    top_right_corner->setDrawChar('-');
    physics->addChild(top_right_corner);
    delete [] pwp_t_r_c_1;
    delete [] pwp_t_r_c_2;

    // Bottom Right Corner
    double * pwp_b_r_c_1 = douglas::vector::vector(unit_width, (unit_height / 3.0));
    double * pwp_b_r_c_2 = douglas::vector::vector(unit_width - (unit_width / 2.5), 0.0);
    bottom_right_corner = new Wall(pwp_b_r_c_1, pwp_b_r_c_2);
    bottom_right_corner->setDrawChar('-');
    physics->addChild(bottom_right_corner);
    delete [] pwp_b_r_c_1;
    delete [] pwp_b_r_c_2;

    // Bottom Left Corner
    double * pwp_b_l_c_1 = douglas::vector::vector(0.0, (unit_height / 3.0));
    double * pwp_b_l_c_2 = douglas::vector::vector((unit_width / 2.5), 0.0);
    bottom_left_corner = new Wall(pwp_b_l_c_1, pwp_b_l_c_2);
    bottom_left_corner->setDrawChar('-');
    physics->addChild(bottom_left_corner);
    delete [] pwp_b_l_c_1;
    delete [] pwp_b_l_c_2;

    // PinWheel Poles

    double * center = douglas::vector::vector(unit_width / 2.0, unit_height / 2.0);
    double pw_length = (unit_width + unit_height) / 4.0;
    double pw_side = std::sqrt(2 * (pw_length * pw_length));

    // PinWheel Pole 1
    double * r_c_point = douglas::vector::vector(center[0] + pw_length, center[1]);
    pinwheel_1 = new MovableWall(center, r_c_point, true);
    pinwheel_1->setDrawChar('#');
    physics->addChild(pinwheel_1);
    delete [] r_c_point;

    // PinWheel Pole 2
    double * b_c_point = douglas::vector::vector(center[0], center[1] - pw_length);
    pinwheel_2 = new MovableWall(center, b_c_point, true);
    pinwheel_2->setDrawChar('#');
    physics->addChild(pinwheel_2);
    delete [] b_c_point;

    // PinWheel Pole 3
    double * l_c_point = douglas::vector::vector(center[0] - pw_length, center[1]);
    pinwheel_3 = new MovableWall(center, l_c_point, true);
    pinwheel_3->setDrawChar('#');
    physics->addChild(pinwheel_3);
    delete [] l_c_point;

    // PinWheel Pole 4
    double * t_c_point = douglas::vector::vector(center[0], center[1] + pw_length);
    pinwheel_4 = new MovableWall(center, t_c_point, true);
    pinwheel_4->setDrawChar('#');
    physics->addChild(pinwheel_4);
    delete [] t_c_point;

    // Exclude PinWheel from all walls in space
    top_wall->exclude(pinwheel_1);
    top_wall->exclude(pinwheel_2);
    top_wall->exclude(pinwheel_3);
    top_wall->exclude(pinwheel_4);
    left_top_wall->exclude(pinwheel_1);
    left_top_wall->exclude(pinwheel_2);
    left_top_wall->exclude(pinwheel_3);
    left_top_wall->exclude(pinwheel_4);
    left_bottom_wall->exclude(pinwheel_1);
    left_bottom_wall->exclude(pinwheel_2);
    left_bottom_wall->exclude(pinwheel_3);
    left_bottom_wall->exclude(pinwheel_4);
    right_top_wall->exclude(pinwheel_1);
    right_top_wall->exclude(pinwheel_2);
    right_top_wall->exclude(pinwheel_3);
    right_top_wall->exclude(pinwheel_4);
    right_bottom_wall->exclude(pinwheel_1);
    right_bottom_wall->exclude(pinwheel_2);
    right_bottom_wall->exclude(pinwheel_3);
    right_bottom_wall->exclude(pinwheel_4);
    bottom_left_wall->exclude(pinwheel_1);
    bottom_left_wall->exclude(pinwheel_2);
    bottom_left_wall->exclude(pinwheel_3);
    bottom_left_wall->exclude(pinwheel_4);
    bottom_right_wall->exclude(pinwheel_1);
    bottom_right_wall->exclude(pinwheel_2);
    bottom_right_wall->exclude(pinwheel_3);
    bottom_right_wall->exclude(pinwheel_4);
    top_left_corner->exclude(pinwheel_1);
    top_left_corner->exclude(pinwheel_2);
    top_left_corner->exclude(pinwheel_3);
    top_left_corner->exclude(pinwheel_4);
    top_right_corner->exclude(pinwheel_1);
    top_right_corner->exclude(pinwheel_2);
    top_right_corner->exclude(pinwheel_3);
    top_right_corner->exclude(pinwheel_4);
    bottom_right_corner->exclude(pinwheel_1);
    bottom_right_corner->exclude(pinwheel_2);
    bottom_right_corner->exclude(pinwheel_3);
    bottom_right_corner->exclude(pinwheel_4);
    bottom_left_corner->exclude(pinwheel_1);
    bottom_left_corner->exclude(pinwheel_2);
    bottom_left_corner->exclude(pinwheel_3);
    bottom_left_corner->exclude(pinwheel_4);

    // PinWheel Pivot
    pinwheel_pivot = new FixedPoint(center);
    pinwheel_pivot->addParticle((Particle*) pinwheel_1->getChildren()[0]);
    pinwheel_pivot->addParticle((Particle*) pinwheel_2->getChildren()[0]);
    pinwheel_pivot->addParticle((Particle*) pinwheel_3->getChildren()[0]);
    pinwheel_pivot->addParticle((Particle*) pinwheel_4->getChildren()[0]);
    physics->addSpecificConstraint(pinwheel_pivot);

    delete [] center;

    // PinWheel LineConstraint 1-3
    pw_lc_1_3 = new LineConstraint(pw_length * 2.0, Constraint::EQUAL);
    pw_lc_1_3->addParticle((Particle*) pinwheel_1->getChildren()[1]);
    pw_lc_1_3->addParticle((Particle*) pinwheel_3->getChildren()[1]);
    physics->addSpecificConstraint(pw_lc_1_3);

    // PinWheel LineConstraint 2-4
    pw_lc_2_4 = new LineConstraint(pw_length * 2.0, Constraint::EQUAL);
    pw_lc_2_4->addParticle((Particle*) pinwheel_2->getChildren()[1]);
    pw_lc_2_4->addParticle((Particle*) pinwheel_4->getChildren()[1]);
    physics->addSpecificConstraint(pw_lc_2_4);

    // PinWheel LineConstraint 1-2
    pw_lc_1_2 = new LineConstraint(pw_side, Constraint::EQUAL);
    pw_lc_1_2->addParticle((Particle*) pinwheel_1->getChildren()[1]);
    pw_lc_1_2->addParticle((Particle*) pinwheel_2->getChildren()[1]);
    physics->addSpecificConstraint(pw_lc_1_2);

    // PinWheel LineConstraint 2-3
    pw_lc_2_3 = new LineConstraint(pw_side, Constraint::EQUAL);
    pw_lc_2_3->addParticle((Particle*) pinwheel_2->getChildren()[1]);
    pw_lc_2_3->addParticle((Particle*) pinwheel_3->getChildren()[1]);
    physics->addSpecificConstraint(pw_lc_2_3);

    // PinWheel LineConstraint 3-4
    pw_lc_3_4 = new LineConstraint(pw_side, Constraint::EQUAL);
    pw_lc_3_4->addParticle((Particle*) pinwheel_3->getChildren()[1]);
    pw_lc_3_4->addParticle((Particle*) pinwheel_4->getChildren()[1]);
    physics->addSpecificConstraint(pw_lc_3_4);

    // PinWheel LineConstraint 4-1
    pw_lc_4_1 = new LineConstraint(pw_side, Constraint::EQUAL);
    pw_lc_4_1->addParticle((Particle*) pinwheel_4->getChildren()[1]);
    pw_lc_4_1->addParticle((Particle*) pinwheel_1->getChildren()[1]);
    physics->addSpecificConstraint(pw_lc_4_1);

    // Add drag to the PinWheel
    pinwheel_drag_constraint = new DragConstraint(1);
    pinwheel_drag_constraint->addParticle((Particle*) pinwheel_1->getChildren()[1]);
    pinwheel_drag_constraint->addParticle((Particle*) pinwheel_2->getChildren()[1]);
    pinwheel_drag_constraint->addParticle((Particle*) pinwheel_3->getChildren()[1]);
    pinwheel_drag_constraint->addParticle((Particle*) pinwheel_4->getChildren()[1]);
    physics->addSpecificConstraint(pinwheel_drag_constraint);

    // Add velocity to the PinWheel
    double * pw_vel = douglas::vector::vector(0.0, 10.0);
    pinwheel_1->addVelocity(pw_vel);
    delete [] pw_vel;

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