//
// Created by Brennan on 3/5/2017.
//

#include "particle.hpp"

Particle::Particle() : GameObject() {
    mass = 1;
}

Particle::Particle(double *pos) : GameObject(pos, nullptr) {
    mass = 1;
}

Particle::Particle(double *pos, double *vel) : GameObject(pos, vel, nullptr) {
    mass = 1;
}

Particle::~Particle() {}

void Particle::step(double dt) {
    GameObject::step(dt);
}

void Particle::render() {

}