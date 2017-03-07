//
// Created by Brennan on 3/6/2017.
//

#include "empty_world.hpp"
#include <string>

std::string EmptyWorld::TYPE = "empty_world";

EmptyWorld::EmptyWorld(int p_w, int p_h, double u_w, double u_h) : Space(p_w, p_h, u_w, u_h) {
    types.push_back(EmptyWorld::TYPE);
    setup();
}

EmptyWorld::EmptyWorld(int p_w, int p_h) : EmptyWorld(p_w, p_h, p_w, p_h) {}

void EmptyWorld::setup() {



}

void EmptyWorld::step(double dt) {
    GameObject::step(dt);

    for(int i = 0; i < EmptyWorld::RELAXATION_ROUNDS; i++) {

    }

}

void EmptyWorld::render() {



}