//
// Created by Brennan on 3/5/2017.
//

#ifndef FINAL_PROJECT_CONSTRAINT_HPP
#define FINAL_PROJECT_CONSTRAINT_HPP

#include "../particle.hpp"
#include <vector>
#include <cmath>

class Constraint {
public:
    enum Equality { EQUAL, LESS_THAN, LESS_THAN_EQUAL, GREATER_THAN, GREATER_THAN_EQUAL};
    enum LINK { PAIR, SINGLE };
protected:
    Constraint::LINK link;
    std::vector<Particle*> particles;
public:

    Constraint(Constraint::LINK l) : link(l) {}
    virtual ~Constraint() {}

    std::vector<Particle*> getParticles() { return particles; }
    void addParticle(Particle* p) { particles.push_back(p); }
    void removeParticle(unsigned int id);

    virtual void fix() = 0;
    virtual void fix(Particle *p1, Particle *p2) = 0;

    static double sqr_dist(Particle *p1, Particle *p2) {
        return (((*p1)[0] - (*p2)[0]) * ((*p1)[0] - (*p2)[0])) + (((*p1)[1] - (*p2)[1]) * ((*p1)[1] - (*p2)[1]));
    }
    static double dist(Particle *p1, Particle *p2) {
        return std::sqrt(sqr_dist(p1, p2));
    }
};

#endif //FINAL_PROJECT_CONSTRAINT_HPP
