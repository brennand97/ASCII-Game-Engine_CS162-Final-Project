//
// Created by Brennan on 3/17/2017.
//

#ifndef FINAL_PROJECT_MOVEABLE_WALL_HPP
#define FINAL_PROJECT_MOVEABLE_WALL_HPP

#include "../particle_container.hpp"
#include "../constraints/single_constraint.hpp"

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

    Particle* p1;
    Particle* p2;

    MovableWallConstraint* movableWallConstraint;

public:

    static std::string TYPE;

    MovableWall(Particle* p1, Particle* p2);

    void render(Screen* screen);

};

#endif //FINAL_PROJECT_MOVEABLE_WALL_HPP
