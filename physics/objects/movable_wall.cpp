//
// Created by Brennan on 3/17/2017.
//

#include "movable_wall.hpp"
#include "../../space.hpp"

std::string MovableWall::TYPE = "movable_wall";
std::string MovableWall::MovableWallConstraint::TYPE = "movable_wall_constraint";

MovableWall::MovableWall(Particle *p1, Particle *p2) {
    addType(MovableWall::TYPE);
    this->p1 = p1;
    this->p2 = p2;
}

void MovableWall::render(Screen *screen) {

    Space* world = (Space*) getWorld();

    double * s_p1 = world->convertToPixels(p1->getPosition(), screen);
    double * s_p2 = world->convertToPixels(p2->getPosition(), screen);

    std::vector<Pixel> line;
    screen->line(s_p1, s_p2, draw_char, &line);
    screen->addToFrame(line);

    delete [] s_p1;
    delete [] s_p2;

}

MovableWall::MovableWallConstraint::MovableWallConstraint(MovableWall *wall) {
    addType(MovableWallConstraint::TYPE);
    this->wall = wall;
}

void MovableWall::MovableWallConstraint::fix(int iter, Particle *p) {
    
}