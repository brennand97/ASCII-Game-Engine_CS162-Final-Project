//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_EMPTY_WORLD_HPP
#define FINAL_PROJECT_EMPTY_WORLD_HPP

#include "space.hpp"
#include <string>

class EmptyWorld : public Space {
public:

    static std::string TYPE;
    constexpr static RELAXATION_ROUNDS = 3;

    EmptyWorld(int p_w, int p_h);
    EmptyWorld(int p_w, int p_h, double u_w, double u_h);
    void setup();
    void render();
    void step(double);

};

#endif //FINAL_PROJECT_EMPTY_WORLD_HPP
