//
// Created by Brennan on 3/18/2017.
//

#ifndef FINAL_PROJECT_TRAPPED_POINT_HPP
#define FINAL_PROJECT_TRAPPED_POINT_HPP

#include "single_constraint.hpp"

class TrappedPoint : public SingleConstraint {
    struct particle_toggle {
        unsigned int id;
        bool trapped;
    };
protected:
    double * point;
    double radius;
    std::vector<particle_toggle> toggles;
    int togglesGetParticleId(Particle* particle);
public:
    static std::string TYPE;
    TrappedPoint(double radius, double * point);
    ~TrappedPoint();
    void fix(int iter, Particle* p);
};

#endif //FINAL_PROJECT_TRAPPED_POINT_HPP
