//
// Created by Brennan on 3/15/2017.
//

#ifndef FINAL_PROJECT_GAME_GRID_L_B_HPP
#define FINAL_PROJECT_GAME_GRID_L_B_HPP

#include "room.hpp"

class GridLB : public Room {
protected:

    Wall* bottom_wall;
    Wall* left_wall;

    Wall* top_left_wall;
    Wall* top_right_wall;
    Wall* right_top_wall;
    Wall* right_bottom_wall;

public:

    static std::string TYPE;
    constexpr static int RELAXATION_ROUNDS = 5;

    GridLB(double u_w, double u_h);

    void setup();
    void step(double dt);
    void render(Screen* screen);

};

#endif // FINAL_PROJECT_GAME_GRID_L_B_HPP