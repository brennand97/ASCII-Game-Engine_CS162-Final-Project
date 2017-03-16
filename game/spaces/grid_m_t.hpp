//
// Created by Brennan on 3/15/2017.
//

#ifndef FINAL_PROJECT_GAME_GRID_M_T_HPP
#define FINAL_PROJECT_GAME_GRID_M_T_HPP

#include "../../space.hpp"

class GridMT : public Space {

public:

    static std::string TYPE;
    constexpr static int RELAXATION_ROUNDS = 5;

    GridMT(double u_w, double u_h);

    void setup();
    void step(double dt);
    void render(Screen* screen);

};

#endif // FINAL_PROJECT_GAME_GRID_M_T_HPP