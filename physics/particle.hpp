//
// Created by Brennan on 3/5/2017.
//

#ifndef FINAL_PROJECT_PHYSICS_PARTICLE_HPP
#define FINAL_PROJECT_PHYSICS_PARTICLE_HPP

#include "../game_object.hpp"
#include <string>

class Particle : public GameObject {
protected:
    double *ppos;
    double *pos;
    double mass;
public:

    static std::string TYPE;

    // Gravitation Constant
    constexpr static double g_accl = 10;

    // Constructors
    Particle();
    Particle(double * pos);
    Particle(double * pos, double * vel);
    Particle(const Particle& obj);
    ~Particle();

    // Physics Data
    double getMass() { return mass; }
    void setMass(double mass) { this->mass = mass; }

    // Position Data
    const double * getPosition() { return pos; }
    void setPosition(double * pos) { delete [] pos; this->pos = pos; }
    const double * getPPosition() { return ppos; }
    void setPPosition(double * ppos) { delete [] ppos; this->ppos = ppos; }

    void step(double dt);
    void render(Screen*);

    double &operator [](const int i) { return pos[i]; }
};

#endif //FINAL_PROJECT_PHYSICS_PARTICLE_HPP
