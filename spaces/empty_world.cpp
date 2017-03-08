//
// Created by Brennan on 3/6/2017.
//

#include "empty_world.hpp"
#include "../physics/constraints/line_constraint.hpp"
#include "../physics/constraints/drag_constraint.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

std::string EmptyWorld::TYPE = "empty_world";

EmptyWorld::EmptyWorld(int p_w, int p_h, double u_w, double u_h) : Space(p_w, p_h, u_w, u_h) {
    addType(EmptyWorld::TYPE);
    setup();
}

EmptyWorld::EmptyWorld(int p_w, int p_h) : EmptyWorld(p_w, p_h, p_w, p_h) {}

void EmptyWorld::setup() {

    double * pos1 = new double[2];
    double * vel1 = new double[2];
    pos1[0] = (unit_width / 2) - 3;
    pos1[1] = (unit_height / 2) - 2;
    vel1[0] = 80;
    vel1[1] = 0;
    Particle* p1 = new Particle(pos1, vel1);
    delete vel1;

    double * pos2 = new double[2];
    double * vel2 = new double[2];
    pos2[0] = (unit_width / 2) + 2;
    pos2[1] = (unit_height / 2) - 3;
    vel2[0] = 0;
    vel2[1] = -160;
    Particle* p2 = new Particle(pos2);
    delete vel2;

    LineConstraint* lc = new LineConstraint(10, Constraint::Equality::EQUAL);
    lc->addParticle(p1);
    lc->addParticle(p2);
//    DragConstraint* dc = new DragConstraint(0.1);
//    dc->addParticle(p1);
//    dc->addParticle(p2);

    physics->addChild(p1);
    physics->addChild(p2);
    physics->addSpecificConstraint(lc);
//    physics->addSpecificConstraint(dc);

}

void EmptyWorld::step(double dt) {

    GameObject::step(dt);

    handlePhysics(EmptyWorld::RELAXATION_ROUNDS);

}

void EmptyWorld::render() {

    int p1_i = std::floor((*((Particle*) physics->getChildren()[0]))[0]) / getXUnitsPerPixel();
    p1_i = std::max(std::min(p1_i, pixel_width - 1), 0);
    int p1_j = std::floor((*((Particle*) physics->getChildren()[0]))[1]) / getYUnitsPerPixel();
    p1_j = std::max(std::min(p1_j, pixel_height - 1), 0);
    int p2_i = std::floor((*((Particle*) physics->getChildren()[1]))[0]) / getXUnitsPerPixel();
    p2_i = std::max(std::min(p2_i, pixel_width - 1), 0);
    int p2_j = std::floor((*((Particle*) physics->getChildren()[1]))[1]) / getYUnitsPerPixel();
    p2_j = std::max(std::min(p2_j, pixel_height - 1), 0);

    frame[p1_i][p1_j] = '*';
    frame[p2_i][p2_j] = '*';

    for(int j = pixel_height - 1; j >= 0; j--) {
        for(int i = 0; i < pixel_width; i++) {
            if(frame[i][j] != ' ') {
                std::cout << frame[i][j];
            } else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }

    frame[p1_i][p1_j] = ' ';
    frame[p2_i][p2_j] = ' ';

}