//
// Created by Brennan on 3/15/2017.
//

#ifndef FINAL_PROJECT_GAME_GRID_M_T_HPP
#define FINAL_PROJECT_GAME_GRID_M_T_HPP

#include "room.hpp"
#include "../../physics/objects/movable_wall.hpp"
#include "../../physics/constraints/fixed_point.hpp"
#include "../../physics/constraints/drag_constraint.hpp"

class GridMT : public Room {
protected:

    Wall* top_wall;

    Wall* left_top_wall;
    Wall* left_bottom_wall;
    Wall* right_top_wall;
    Wall* right_bottom_wall;
    Wall* bottom_left_wall;
    Wall* bottom_right_wall;

    // For Pinwheel Puzzle

    Wall* top_left_corner;
    Wall* top_right_corner;
    Wall* bottom_right_corner;
    Wall* bottom_left_corner;

    MovableWall* pinwheel_1;
    MovableWall* pinwheel_2;
    MovableWall* pinwheel_3;
    MovableWall* pinwheel_4;

    FixedPoint* pinwheel_pivot;

    LineConstraint* pw_lc_1_3;
    LineConstraint* pw_lc_2_4;
    LineConstraint* pw_lc_1_2;
    LineConstraint* pw_lc_2_3;
    LineConstraint* pw_lc_3_4;
    LineConstraint* pw_lc_4_1;

    DragConstraint* pinwheel_drag_constraint;

public:

    static std::string TYPE;
    constexpr static int RELAXATION_ROUNDS = 5;

    GridMT(double u_w, double u_h);

    void setup();
    void step(double dt);
    void render(Screen* screen);

};

#endif // FINAL_PROJECT_GAME_GRID_M_T_HPP