//
// Created by Brennan on 3/15/2017.
//

#ifndef FINAL_PROJECT_GAME_GRID_R_T_HPP
#define FINAL_PROJECT_GAME_GRID_R_T_HPP

#include "room.hpp"

class GridRT : public Room {

public:

    static std::string TYPE;
    constexpr static int RELAXATION_ROUNDS = 5;

    GridRT(double u_w, double u_h);

    void setup();
    void step(double dt);
    void render(Screen* screen);

};

#endif // FINAL_PROJECT_GAME_GRID_R_T_HPP