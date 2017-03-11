//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_PARTICLE_CONTAINER_HPP
#define FINAL_PROJECT_PARTICLE_CONTAINER_HPP

#include "../game_object.hpp"
#include "constraints/constraint.hpp"
#include "constraints/single_constraint.hpp"
#include <string>
#include <vector>

class ParticleContainer : public GameObject {
protected:
    std::vector<Constraint*> specific_constraints;
    std::vector<SingleConstraint*> sub_global_constraints;
public:

    static std::string TYPE;

    // Constructors
    ParticleContainer();
    virtual ~ParticleContainer();

    void addSpecificConstraint(Constraint*);
    void addSubGlobalConstraint(SingleConstraint*);

    void getGlobalConstraints(std::vector<SingleConstraint*>*);
    std::vector<SingleConstraint*> getSubGlobalConstraints() { return sub_global_constraints; }
    void getSubGlobalConstraints(std::vector<SingleConstraint*>*);
    std::vector<Constraint*> getSpecificConstraints() { return specific_constraints; }
    void getSpecificConstraints(std::vector<Constraint*>*);

    void handleConstraints(int);

    virtual void render(Screen*) {}

};

#endif //FINAL_PROJECT_PARTICLE_CONTAINER_HPP
