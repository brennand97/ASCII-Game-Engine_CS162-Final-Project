//
// Created by Brennan on 3/15/2017.
//

#ifndef FINAL_PROJECT_GAME_GRID_R_B_HPP
#define FINAL_PROJECT_GAME_GRID_R_B_HPP

#include "../../space.hpp"

class GridRB : public Space {

public:

    static std::string TYPE;
    constexpr static int RELAXATION_ROUNDS = 5;

    GridRB(double u_w, double u_h);

    void setup();
    void step(double dt);
    void render(Screen* screen);

};

#endif // FINAL_PROJECT_GAME_GRID_R_B_HPP