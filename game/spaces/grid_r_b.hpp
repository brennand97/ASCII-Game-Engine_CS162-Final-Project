//
// Created by Brennan on 3/15/2017.
//

#ifndef FINAL_PROJECT_GAME_GRID_R_B_HPP
#define FINAL_PROJECT_GAME_GRID_R_B_HPP

#include "room.hpp"

class GridRB : public Room {
protected:

    Wall* right_wall;
    Wall* bottom_wall;

    Wall* left_top_wall;
    Wall* left_bottom_wall;
    Wall* top_left_wall;
    Wall* top_right_wall;

    Wall * tunnel_top_left_wall;
    Wall * tunnel_top_right_wall;
    Wall * tunnel_middle_top_wall;
    Wall * tunnel_middle_bottom_wall;

public:

    static std::string TYPE;
    constexpr static int RELAXATION_ROUNDS = 5;

    GridRB(double u_w, double u_h);

    void setup();
    void step(double dt);
    void render(Screen* screen);

};

#endif // FINAL_PROJECT_GAME_GRID_R_B_HPP