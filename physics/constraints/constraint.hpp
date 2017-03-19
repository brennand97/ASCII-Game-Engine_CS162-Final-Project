//
// Created by Brennan on 3/5/2017.
//

#ifndef FINAL_PROJECT_CONSTRAINT_HPP
#define FINAL_PROJECT_CONSTRAINT_HPP

#include "../../typed.hpp"
#include "../particle.hpp"
#include <vector>
#include <string>
#include <cmath>

class Constraint : public Typed {
protected:
    std::vector<Particle*> particles;
    std::vector<unsigned int> excluded;
public:

    enum Equality { EQUAL, LESS_THAN, LESS_THAN_EQUAL, GREATER_THAN, GREATER_THAN_EQUAL};

    static std::string TYPE;

    Constraint() : Typed(Constraint::TYPE) {}
    virtual ~Constraint() {}

    std::vector<Particle*> getParticles() { return particles; }
    void addParticle(Particle* p) { particles.push_back(p); }
    void removeParticle(unsigned int id);

    void exclude(GameObject* go);
    bool isExcluded(GameObject* go);

    virtual void fix(int iter) = 0;

    static double sqr_dist(Particle *p1, Particle *p2) {
        return (((*p1)[0] - (*p2)[0]) * ((*p1)[0] - (*p2)[0])) + (((*p1)[1] - (*p2)[1]) * ((*p1)[1] - (*p2)[1]));
    }
    static double dist(Particle *p1, Particle *p2) {
        return std::sqrt(sqr_dist(p1, p2));
    }
};

#endif //FINAL_PROJECT_CONSTRAINT_HPP
