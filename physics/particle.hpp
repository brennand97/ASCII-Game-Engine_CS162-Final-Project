//
// Created by Brennan on 3/5/2017.
//

#ifndef FINAL_PROJECT_PHYSICS_PARTICLE_HPP
#define FINAL_PROJECT_PHYSICS_PARTICLE_HPP

#include "../game_object.hpp"

class Particle : public GameObject {
public:
    Particle();
    Particle(double * pos);
    Particle(double * pos, double * vel);
    ~Particle();
    void step(double dt);
    void render();
};

#endif //FINAL_PROJECT_PHYSICS_PARTICLE_HPP
