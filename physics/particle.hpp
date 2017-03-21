/**
 * Author:      Brennan Douglas
 * Date:        03/05/2017
 * Description: This is the header file for the Particle class
 */

#ifndef FINAL_PROJECT_PHYSICS_PARTICLE_HPP
#define FINAL_PROJECT_PHYSICS_PARTICLE_HPP

#include "../game_object.hpp"
#include <string>

// Represents a particle that can move around the world with velocity and interact with the environment
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
    void setPosition(const double * pos) { this->pos[0] = pos[0]; this->pos[1] = pos[1]; }
    const double * getPPosition() { return ppos; }
    void setPPosition(const double * ppos) { this->ppos[0] = ppos[0]; this->ppos[1] = ppos[1]; }

    void step(double dt);
    void render(Screen*);

    double &operator [](const int i) { return pos[i]; }
};

#endif //FINAL_PROJECT_PHYSICS_PARTICLE_HPP
