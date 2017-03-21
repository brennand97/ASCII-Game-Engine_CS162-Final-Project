/**
 * Author:      Brennan Douglas
 * Date:        03/16/2017
 * Description: This is the header file for the Wall class
 */

#ifndef FINAL_PROJECT_WALL_HPP
#define FINAL_PROJECT_WALL_HPP

#include "../particle_container.hpp"
#include "../constraints/single_constraint.hpp"

// Wall is a static wall that moving particles cannot pass through
class Wall : public ParticleContainer {
public:
    class WallConstraint : public SingleConstraint {
    protected:
        Wall* wall;
    public:
        static std::string TYPE;
        WallConstraint(Wall* wall1);
        void fix(int, Particle*);
    };

protected:
    double* top;
    double* bottom;
    WallConstraint* wallConstraint;
public:
    static std::string TYPE;
    Wall(double * top, double * bottom);
    ~Wall();
    void exclude(GameObject* go) { wallConstraint->exclude(go); }
    void render(Screen* screen);
};

#endif //FINAL_PROJECT_WALL_HPP
