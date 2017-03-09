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
#include <cmath>

std::string EmptyWorld::TYPE = "empty_world";

EmptyWorld::EmptyWorld(double u_w, double u_h) : Space(u_w, u_h) {
    addType(EmptyWorld::TYPE);
    setup();
}

void EmptyWorld::setup() {

    double * pos1 = new double[2];
    double * vel1 = new double[2];
    pos1[0] = (unit_width / 2) - 3;
    pos1[1] = (unit_height / 2) - 2;
    vel1[0] = 20;
    vel1[1] = 0;
    Particle* p1 = new Particle(pos1, vel1);
    delete vel1;

    double * pos2 = new double[2];
    double * vel2 = new double[2];
    pos2[0] = (unit_width / 2) + 2;
    pos2[1] = (unit_height / 2) - 3;
    vel2[0] = 0;
    vel2[1] = 2;
    Particle* p2 = new Particle(pos2, vel2);
    delete vel2;

    for(int i = 0; i < 10; i++) {
        double *pos3 = new double[2];
        double *vel3 = new double[2];
        pos3[0] = (unit_width / 2) + 2;
        pos3[1] = (unit_height / 2) - 3;
        vel3[0] = std::sin((2*3.14) * i / 10);
        vel3[1] = std::cos((2*3.14) * i / 10);
        Particle *p3 = new Particle(pos3, vel3);
        delete vel3;

        physics->addChild(p3);
    }

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

void EmptyWorld::render(Screen* screen) {

    double x_upp = unit_width / screen->getWidth();
    double y_upp = unit_height / screen->getHeight();

    int p1_i = std::floor((*((Particle*) physics->getChildren()[0]))[0]) / x_upp;
    int p1_j = std::floor((*((Particle*) physics->getChildren()[0]))[1]) / y_upp;
    int p2_i = std::floor((*((Particle*) physics->getChildren()[1]))[0]) / x_upp;
    int p2_j = std::floor((*((Particle*) physics->getChildren()[1]))[1]) / y_upp;

    double * p1 = new double[2];
    p1[0] = (*((Particle*) physics->getChildren()[0]))[0] / x_upp;
    p1[1] = (*((Particle*) physics->getChildren()[0]))[1] / y_upp;
    double * p2 = new double[2];
    p2[0] = (*((Particle*) physics->getChildren()[1]))[0] / x_upp;
    p2[1] = (*((Particle*) physics->getChildren()[1]))[1] / y_upp;

    std::vector<Pixel> line = screen->getLine(p1, p2, '#');

    screen->addToFrame(line);

}