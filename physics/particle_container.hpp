/**
 * Author:      Brennan Douglas
 * Date:        03/06/2017
 * Description: This is the header file for the ParticleContainer class
 */

#ifndef FINAL_PROJECT_PARTICLE_CONTAINER_HPP
#define FINAL_PROJECT_PARTICLE_CONTAINER_HPP

#include "../game_object.hpp"
#include "constraints/constraint.hpp"
#include "constraints/single_constraint.hpp"
#include <string>
#include <vector>

// A recursively designed component that resolves all physics constraints at its level in the GameObject tree.
// Any physics that happens is inside of a ParticleContainer.
class ParticleContainer : public GameObject {
private:
    // Caching mechanism to decrease amount of recursive calls
    std::vector<SingleConstraint*> cached_global_constraints;
    std::vector<SingleConstraint*> master_cached_global_super_constraints;
protected:
    std::vector<Constraint*> specific_constraints;
    std::vector<SingleConstraint*> sub_global_constraints;
    std::vector<SingleConstraint*> super_global_constraints;
public:

    static std::string TYPE;

    // Constructors
    ParticleContainer();
    ~ParticleContainer();

    void addSpecificConstraint(Constraint*);
    void addSubGlobalConstraint(SingleConstraint*);
    void addSuperGlobalConstraint(SingleConstraint*);

    void getGlobalConstraints(std::vector<SingleConstraint*>* vec, bool update_cached = false, bool supers = true);
    std::vector<SingleConstraint*> getSubGlobalConstraints() { return sub_global_constraints; }
    void getSubGlobalConstraints(std::vector<SingleConstraint*>*);
    void removeSubGlobalConstraint(int index);
    std::vector<SingleConstraint*> getSuperGlobalConstraints() { return super_global_constraints; }
    void getSuperGlobalConstraints(std::vector<SingleConstraint*>*, bool update_cached = false);
    std::vector<Constraint*> getSpecificConstraints() { return specific_constraints; }
    void getSpecificConstraints(std::vector<Constraint*>*);

    void addVelocity(double* vel);

    void handleConstraints(int);

    virtual void render(Screen* screen) {
        renderChildren(screen);
    }

};

#endif //FINAL_PROJECT_PARTICLE_CONTAINER_HPP
