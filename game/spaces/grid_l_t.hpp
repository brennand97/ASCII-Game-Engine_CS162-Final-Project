//
// Created by Brennan on 3/15/2017.
//

#ifndef FINAL_PROJECT_GAME_GRID_L_T_HPP
#define FINAL_PROJECT_GAME_GRID_L_T_HPP

#include "room.hpp"
#include "../key.hpp"
#include "../key.hpp"

class GridLT : public Room {
protected:

    Wall* left_wall;
    Wall* top_wall;

    Wall* right_top_wall;
    Wall* right_bottom_wall;
    Wall* bottom_left_wall;
    Wall* bottom_right_wall;

    Key* key;

public:

    static std::string TYPE;
    constexpr static int RELAXATION_ROUNDS = 5;

    GridLT(double u_w, double u_h);

    Key* getKey() { return key; }

    void setup();
    void step(double dt);
    void render(Screen* screen);

};

#endif // FINAL_PROJECT_GAME_GRID_L_T_HPP