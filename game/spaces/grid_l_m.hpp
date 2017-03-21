//
// Created by Brennan on 3/15/2017.
//

#ifndef FINAL_PROJECT_GAME_GRID_L_M_HPP
#define FINAL_PROJECT_GAME_GRID_L_M_HPP

#include "room.hpp"
#include "../../physics/objects/movable_wall.hpp"
#include "../../physics/constraints/fixed_point.hpp"
#include "../../physics/constraints/trapped_point.hpp"
#include "../key.hpp"

class GridLM : public Room {
protected:

    Wall* left_wall;

    Wall* top_left_wall;
    Wall* top_right_wall;
    Wall* right_top_wall;
    Wall* right_bottom_wall;
    Wall* bottom_left_wall;
    Wall* bottom_right_wall;

    Wall * tunnel_bottom_left_wall;
    Wall * tunnel_bottom_right_wall;
    Wall * tunnel_middle_top_wall;
    Wall * tunnel_middle_bottom_wall;

    // For rotating puzzle piece
    MovableWall* left_arm;
    MovableWall* right_arm;
    Wall* blocking_right_wall;
    FixedPoint* pivot_point;
    TrappedPoint* left_stop;
    TrappedPoint* right_stop;
    LineConstraint* rigid_connector;

    // Key
    Key* key;

public:

    static std::string TYPE;
    constexpr static int RELAXATION_ROUNDS = 5;

    GridLM(double u_w, double u_h);

    Key* getKey() { return key; }

    void setup();
    void step(double dt);
    void render(Screen* screen);

};

#endif // FINAL_PROJECT_GAME_GRID_L_M_HPP