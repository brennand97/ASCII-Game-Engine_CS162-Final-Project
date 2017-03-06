//
// Created by Brennan on 3/6/2017.
//

#include "empty_world.hpp"

EmptyWorld::EmptyWorld(int p_w, int p_h, double u_w, double u_h) : Space(p_w, p_h, u_w, u_h) {

}

EmptyWorld::EmptyWorld(int p_w, int p_h) : EmptyWorld(p_w, p_h, p_w, p_h) {}

void EmptyWorld::step(double dt) {



    stepChildren(dt);
    previous_dt = dt;

}

void EmptyWorld::render() {



}