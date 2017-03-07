//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_PARTICLE_CONTAINER_HPP
#define FINAL_PROJECT_PARTICLE_CONTAINER_HPP

#include "../game_object.hpp"
#include "constraints/constraint.hpp"
#include <string>
#include <vector>

class ParticleContainer : public GameObject {
private:
    std::vector<Constraint*> specific_constraints;
    std::vector<Constraint*> sub_global_constraints;
public:

    static std::string TYPE;

    // Constructors
    ParticleContainer();

    void getGlobalConstraints(std::vector<Constraint*>*);
    std::vector<Constraint*> getSubGlobalConstraints() { return sub_global_constraints; }
    void getSubGlobalConstraints(std::vector<Constraint*>*);
    std::vector<Constraint*> getSpecificConstraints() { return specific_constraints; }
    void getSpecificConstraints(std::vector<Constraint*>*);

};

#endif //FINAL_PROJECT_PARTICLE_CONTAINER_HPP
