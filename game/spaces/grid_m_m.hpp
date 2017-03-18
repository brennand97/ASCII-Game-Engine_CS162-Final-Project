//
// Created by Brennan on 3/15/2017.
//

#ifndef FINAL_PROJECT_GAME_GRID_M_M_HPP
#define FINAL_PROJECT_GAME_GRID_M_M_HPP

#include "room.hpp"

class GridMM : public Room {
protected:

    Wall* left_top_wall;
    Wall* left_bottom_wall;
    Wall* top_left_wall;
    Wall* top_right_wall;
    Wall* right_top_wall;
    Wall* right_bottom_wall;
    Wall* bottom_left_wall;
    Wall* bottom_right_wall;

public:

    static std::string TYPE;
    constexpr static int RELAXATION_ROUNDS = 5;

    GridMM(double u_w, double u_h);

    void setup();
    void step(double dt);
    void render(Screen* screen);

};

#endif // FINAL_PROJECT_GAME_GRID_M_M_HPP