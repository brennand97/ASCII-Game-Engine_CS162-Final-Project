/**
 * Author:          Brennan Douglas
 * Date:            03/15/2017
 * Description:     One of the implementations of Space
 */

#include "grid_m_m.hpp"

// Type declaration
std::string GridMM::TYPE = "grid_middle_middle";

// Default constructor
GridMM::GridMM(double u_w, double u_h) : Room(u_w, u_h) {
    // Add type to type list
    addType(GridMM::TYPE);
    // Call virtual setup function
    setup();
}

// Setup function, set's up the environment
void GridMM::setup() {
    // Makes the boundary slightly bouncy
    boundary->setRigid(0);

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
void GridMM::step(double dt) {
    GameObject::step(dt);
    handlePhysics(GridMM::RELAXATION_ROUNDS);
}

// Renders the space
void GridMM::render(Screen *screen) {

    // Inform player about the room
    screen->printValue(7, " Info:      To complete this game,");
    screen->printValue(8, "            please bring 3 keys to");
    screen->printValue(9, "            this room. Your progress");
    screen->printValue(10,"            will be denoted in the");
    screen->printValue(11,"            box on the floor. There");
    screen->printValue(12,"            are 9 rooms which can be");
    screen->printValue(13,"            accessed by the doors in");
    screen->printValue(14,"            the walls.");
    screen->printValue(16," Movement:  WASD keys");

    double * t_l = douglas::vector::vector((unit_width / 3.0), unit_height - (unit_height / 3.0));
    double * t_r = douglas::vector::vector(unit_width - (unit_width / 3.0), unit_height - (unit_height / 3.0));
    double * b_r = douglas::vector::vector(unit_width - (unit_width / 3.0), (unit_height / 3.0));
    double * b_l = douglas::vector::vector((unit_width / 3.0), (unit_height / 3.0));

    Space* world = (Space*) getWorld();
    world->convertToPixels(t_l, screen);
    world->convertToPixels(t_r, screen);
    world->convertToPixels(b_r, screen);
    world->convertToPixels(b_l, screen);

    std::vector<Pixel> box;
    screen->line(t_l, t_r, '.', &box);
    screen->line(b_l, b_r, '.', &box);
    screen->line(t_l, b_l, '.', &box);
    screen->line(t_r, b_r, '.', &box);
    screen->addToFrame(box);

    std::vector<Pixel> ticks;
    if(show_marker_1) {
        double * p1 = douglas::vector::vector((unit_width / 2.5), unit_height - (unit_height / 2.5));
        double * p2 = douglas::vector::vector((unit_width / 2.5), (unit_height / 2.5));
        world->convertToPixels(p1, screen);
        world->convertToPixels(p2, screen);
        screen->line(p1, p2, '.', &ticks);
        delete [] p1;
        delete [] p2;
    }

    if(show_marker_2) {
        double * p1 = douglas::vector::vector((unit_width / 2.0), unit_height - (unit_height / 2.5));
        double * p2 = douglas::vector::vector((unit_width / 2.0), (unit_height / 2.5));
        world->convertToPixels(p1, screen);
        world->convertToPixels(p2, screen);
        screen->line(p1, p2, '.', &ticks);
        delete [] p1;
        delete [] p2;
    }

    if(show_marker_3) {
        double * p1 = douglas::vector::vector(unit_width - (unit_width / 2.5), unit_height - (unit_height / 2.5));
        double * p2 = douglas::vector::vector(unit_width - (unit_width / 2.5), (unit_height / 2.5));
        world->convertToPixels(p1, screen);
        world->convertToPixels(p2, screen);
        screen->line(p1, p2, '.', &ticks);
        delete [] p1;
        delete [] p2;
    }

    screen->addToFrame(ticks);

    delete [] t_l;
    delete [] t_r;
    delete [] b_r;
    delete [] b_l;

    // Renders all the children
    renderChildren(screen);
}

void GridMM::setMarker(int i, bool b) {
    switch (i) {
        case 1: {
            show_marker_1 = b;
            break;
        }
        case 2: {
            show_marker_2 = b;
            break;
        }
        case 3: {
            show_marker_3 = b;
            break;
        }
    }
}