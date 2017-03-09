//
// Created by Brennan on 3/5/2017.
//

#include "particle.hpp"
#include <string>

std::string Particle::TYPE = "particle";

Particle::Particle() : GameObject() {
    addType(Particle::TYPE);
    mass = 1;
    pos = new double[2];
    pos[0] = 0;
    pos[1] = 0;
    ppos = new double[2];
    ppos[0] = 0;
    ppos[1] = 0;
}

Particle::Particle(double *pos) : GameObject() {
    addType(Particle::TYPE);
    mass = 1;
    if(pos != nullptr) {
        this->pos = pos;
    } else {
        pos = new double[2];
        pos[0] = 0;
        pos[1] = 0;
    }
    this->ppos = new double[2];
    ppos[0] = pos[0];
    ppos[1] = pos[1];
}

Particle::Particle(double *pos, double *vel) : GameObject() {
    addType(Particle::TYPE);
    mass = 1;
    if(pos != nullptr) {
        this->pos = pos;
    } else {
        pos = new double[2];
        pos[0] = 0;
        pos[1] = 0;
    }
    this->ppos = new double[2];
    if(vel != nullptr) {
        ppos[0] = pos[0] - vel[0];
        ppos[1] = pos[1] - vel[1];
    } else {
        ppos[0] = pos[0];
        ppos[1] = pos[1];
    }
}

Particle::~Particle() {
    delete [] pos;
    delete [] ppos;
}

void Particle::step(double dt) {

    if(previous_dt < 0) {
        previous_dt = dt;
    }

    double *n_pos = new double[2];
    double *vel = new double[2];

    vel[0] = (pos[0] - ppos[0]) / previous_dt;
    vel[1] = (pos[1] - ppos[1]) / previous_dt;

    n_pos[0] = pos[0] + (vel[0] * dt);
    n_pos[1] = pos[1] + (vel[1] * dt);

    delete [] ppos;
    ppos = pos;
    pos = n_pos;

    delete [] vel;

    stepChildren(dt);

    previous_dt = dt;

}

void Particle::render(Screen* screen) {

}