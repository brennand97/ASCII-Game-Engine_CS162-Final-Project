//
// Created by Brennan on 3/17/2017.
//

#ifndef FINAL_PROJECT_MOVEABLE_WALL_HPP
#define FINAL_PROJECT_MOVEABLE_WALL_HPP

#include "../particle_container.hpp"
#include "../constraints/single_constraint.hpp"
#include "../constraints/line_constraint.hpp"

class MovableWall : public ParticleContainer {
public:
    // NOTE this constraint does not take particle masses into account
    class MovableWallConstraint : public SingleConstraint {
    protected:
        MovableWall* wall;
    public:
        static std::string TYPE;
        MovableWallConstraint(MovableWall* wall);
        void fix(int iter, Particle* p);
    };

protected:

    bool wall_moves;

    Particle* p1;
    Particle* p2;

    LineConstraint* lineConstraint;
    MovableWallConstraint* movableWallConstraint;

public:

    static std::string TYPE;

    MovableWall(double* p1, double* p2, bool wall_moves = true);

    void exclude(GameObject* go) { movableWallConstraint->exclude(go); }

    void render(Screen* screen);

};

#endif //FINAL_PROJECT_MOVEABLE_WALL_HPP
