//
// Created by Brennan on 3/15/2017.
//

#ifndef FINAL_PROJECT_GAME_GRID_R_T_HPP
#define FINAL_PROJECT_GAME_GRID_R_T_HPP

#include "room.hpp"
#include "../../physics/objects/movable_wall.hpp"
#include "../../physics/constraints/drag_constraint.hpp"
#include "../key.hpp"

class GridRT : public Room {
protected:

    Wall* right_wall;
    Wall* top_wall;

    Wall* left_top_wall;
    Wall* left_bottom_wall;
    Wall* bottom_left_wall;
    Wall* bottom_right_wall;

    ParticleContainer* mvs;
    MovableWall* mv1;
    MovableWall* mv2;
    MovableWall* mv3;

    DragConstraint* mvs_drag;

    Key* key;

public:

    static std::string TYPE;
    constexpr static int RELAXATION_ROUNDS = 5;

    GridRT(double u_w, double u_h);

    Key* getKey() { return key; }

    void setup();
    void step(double dt);
    void render(Screen* screen);

};

#endif // FINAL_PROJECT_GAME_GRID_R_T_HPP