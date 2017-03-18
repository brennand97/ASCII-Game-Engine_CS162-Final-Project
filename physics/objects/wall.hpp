//
// Created by Brennan on 3/16/2017.
//

#ifndef FINAL_PROJECT_WALL_HPP
#define FINAL_PROJECT_WALL_HPP

#include "../particle_container.hpp"
#include "../constraints/single_constraint.hpp"

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
    void render(Screen* screen);
};

#endif //FINAL_PROJECT_WALL_HPP
