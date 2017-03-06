//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_EMPTY_WORLD_HPP
#define FINAL_PROJECT_EMPTY_WORLD_HPP

#include "space.hpp"

class EmptyWorld : public Space {
public:
    EmptyWorld(int p_w, int p_h);
    EmptyWorld(int p_w, int p_h, double u_w, double u_h);
    void render();
    void step(double);
};

#endif //FINAL_PROJECT_EMPTY_WORLD_HPP
