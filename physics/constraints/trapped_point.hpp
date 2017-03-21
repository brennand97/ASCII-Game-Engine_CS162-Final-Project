/**
 * Author:      Brennan Douglas
 * Date:        03/18/2017
 * Description: This is the header file for the TrappedPoint class
 */

#ifndef FINAL_PROJECT_TRAPPED_POINT_HPP
#define FINAL_PROJECT_TRAPPED_POINT_HPP

#include "single_constraint.hpp"

// Defines a constraint where when a specified particle comes within a specified distance it will become fixed to it.
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
