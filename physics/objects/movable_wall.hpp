/**
 * Author:      Brennan Douglas
 * Date:        03/17/2017
 * Description: This is the header file for the MovableWall class
 */

#ifndef FINAL_PROJECT_MOVEABLE_WALL_HPP
#define FINAL_PROJECT_MOVEABLE_WALL_HPP

#include "../particle_container.hpp"
#include "../constraints/single_constraint.hpp"
#include "../constraints/line_constraint.hpp"

// This class is basically a stick that can be push and rotated by all Particles in a ParticleContainer and in the
// same GameObject tree as it is.
class MovableWall : public ParticleContainer {
public:
    // NOTE this constraint does not take particle masses into account, or that the wall is moving (this causes some funny glitches)
    class MovableWallConstraint : public SingleConstraint {
    protected:
        MovableWall* wall;
        bool delete_wall = false;
    public:
        static std::string TYPE;
        MovableWallConstraint(MovableWall* wall);
        MovableWallConstraint(Particle* p1, Particle* p2, bool wall_moves = true);
        ~MovableWallConstraint();
        void setWallMove(bool b) { this->wall->wall_moves = b; }
        void fix(int iter, Particle* p);
    };

protected:

    bool wall_moves;

    Particle* p1;
    Particle* p2;

    LineConstraint* lineConstraint;
    MovableWallConstraint* movableWallConstraint;

    MovableWall(Particle* p1, Particle* p2, bool wall_moves = true);

public:

    static std::string TYPE;

    MovableWall(double* p1, double* p2, bool wall_moves = true);

    void exclude(GameObject* go) { movableWallConstraint->exclude(go); }

    void render(Screen* screen);

};

#endif //FINAL_PROJECT_MOVEABLE_WALL_HPP
