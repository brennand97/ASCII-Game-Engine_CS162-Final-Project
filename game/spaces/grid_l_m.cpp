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

    // Left Wall
    double * l_w_t = douglas::vector::vector( 0.0, unit_height + (unit_height / 2.0));
    double * l_w_b = douglas::vector::vector( 0.0, - (unit_height / 2.0));
    left_wall = new Wall(l_w_t, l_w_b);
    left_wall->setDrawChar('|');
    physics->addChild(left_wall);
    delete [] l_w_t;
    delete [] l_w_b;

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

    // Tunnel Walls

    // Tunnel Bottom Left Wall
    double * t_b_l_w_1 = douglas::vector::vector( (unit_width / 2.5), 0.0);
    double * t_b_l_w_2 = douglas::vector::vector( (unit_width / 2.5), unit_height - (unit_height / 3.0));
    tunnel_bottom_left_wall = new Wall(t_b_l_w_1, t_b_l_w_2);
    tunnel_bottom_left_wall->setDrawChar('|');
    physics->addChild(tunnel_bottom_left_wall);
    delete [] t_b_l_w_1;
    delete [] t_b_l_w_2;

    // Tunnel Bottom Right Wall
    double * t_b_r_w_1 = douglas::vector::vector( unit_width - (unit_width / 2.5), 0.0);
    double * t_b_r_w_2 = douglas::vector::vector( unit_width - (unit_width / 2.5), (unit_height / 3.0));
    tunnel_bottom_right_wall = new Wall(t_b_r_w_1, t_b_r_w_2);
    tunnel_bottom_right_wall->setDrawChar('|');
    physics->addChild(tunnel_bottom_right_wall);
    delete [] t_b_r_w_1;
    delete [] t_b_r_w_2;

    // Tunnel Middle Top Wall
    double * t_m_t_w_1 = douglas::vector::vector( (unit_width / 2.5), unit_height - (unit_height / 3.0));
    double * t_m_t_w_2 = douglas::vector::vector( (unit_width - 0.5), unit_height - (unit_height / 3.0));
    tunnel_middle_top_wall = new Wall(t_m_t_w_1, t_m_t_w_2);
    tunnel_middle_top_wall->setDrawChar('_');
    physics->addChild(tunnel_middle_top_wall);
    delete [] t_m_t_w_1;
    delete [] t_m_t_w_2;

    // Tunnel Middle Bottom Wall
    double * t_m_b_w_1 = douglas::vector::vector( unit_width - (unit_width / 2.5), (unit_height / 3.0));
    double * t_m_b_w_2 = douglas::vector::vector( (unit_width - 0.5), (unit_height / 3.0));
    tunnel_middle_bottom_wall = new Wall(t_m_b_w_1, t_m_b_w_2);
    tunnel_middle_bottom_wall->setDrawChar('_');
    physics->addChild(tunnel_middle_bottom_wall);
    delete [] t_m_b_w_1;
    delete [] t_m_b_w_2;

    // Rotating Puzzle Piece

    double * pivot_point_arr = douglas::vector::vector(unit_width * (7.0 / 10.0), unit_height * (2.0 / 9.0));

    double * left_arm_top = douglas::vector::vector(unit_width * (21.0 / 50.0), unit_height * (1.0 / 3.0));
    left_arm = new MovableWall(left_arm_top, pivot_point_arr);
    physics->addChild(left_arm);

    double * right_arm_top = douglas::vector::vector(unit_width * (73.0 / 90.0), unit_height * (59.0 / 90.0));
    right_arm = new MovableWall(right_arm_top, pivot_point_arr, false);
    physics->addChild(right_arm);

    double * left_arm_trap_point = douglas::vector::vector(unit_width * (0.5), unit_height * (2.0 / 3.0));
    left_stop = new TrappedPoint(2, left_arm_trap_point);
    left_stop->addParticle((Particle*) left_arm->getChildren()[0]);
    physics->addSpecificConstraint(left_stop);

    rigid_connector = new LineConstraint(douglas::vector::distance(left_arm_top, right_arm_top), Constraint::EQUAL);
    rigid_connector->addParticle((Particle*) left_arm->getChildren()[0]);
    rigid_connector->addParticle((Particle*) right_arm->getChildren()[0]);
    physics->addSpecificConstraint(rigid_connector);

    pivot_point = new FixedPoint(pivot_point_arr);
    pivot_point->addParticle((Particle*) left_arm->getChildren()[1]);
    pivot_point->addParticle((Particle*) right_arm->getChildren()[1]);
    physics->addSpecificConstraint(pivot_point);

    double * right_arm_vector = douglas::vector::subtract(pivot_point_arr, right_arm_top);
    douglas::vector::unitVector(right_arm_vector);
    douglas::vector::scale(right_arm_vector, 5.0);
    double * right_wall_top_point = douglas::vector::vector(unit_width * (71.0 / 90.0), unit_height * (63.0 / 90.0));
    double * right_wall_bottom_point = douglas::vector::add(right_wall_top_point, right_arm_vector);
    blocking_right_wall = new Wall(right_wall_top_point, right_wall_bottom_point);
    physics->addChild(blocking_right_wall);

    delete [] right_arm_vector;
    delete [] right_wall_top_point;
    delete [] right_wall_bottom_point;
    delete [] pivot_point_arr;
    delete [] left_arm_trap_point;
    delete [] left_arm_top;
    delete [] right_arm_top;

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