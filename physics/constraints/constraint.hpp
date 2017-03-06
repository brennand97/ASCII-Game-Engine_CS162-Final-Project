//
// Created by Brennan on 3/5/2017.
//

#ifndef FINAL_PROJECT_CONSTRAINT_HPP
#define FINAL_PROJECT_CONSTRAINT_HPP

#include "../particle.hpp"
#include <cmath>

class Constraint {
public:
    enum Equality { EQUAL, LESS_THAN, LESS_THAN_EQUAL, GREATER_THAN, GREATER_THAN_EQUAL};
    virtual void fix(Particle* p1, Particle* p2) = 0;
    static double sqr_dist(Particle* p1, Particle* p2) {
        return ((p1[0] - p2[0]) * (p1[0] - p2[0])) + ((p1[1] - p2[1]) * (p1[1] - p2[1]));
    }
};

#endif //FINAL_PROJECT_CONSTRAINT_HPP
