//
// Created by Brennan on 3/5/2017.
//

#ifndef FINAL_PROJECT_SPACE_HPP
#define FINAL_PROJECT_SPACE_HPP

#include "../game_object.hpp"
#include "../physics/constraints/constraint.hpp"
#include <unordered_map>

class Space : public GameObject {
protected:
    double unit_width;
    double unit_height;
    int pixel_width;
    int pixel_height;
public:
    Space(int p_w, int p_h) : GameObject() {
        hit[0] = p_w;
        hit[1] = p_h;
        pixel_width = p_w;
        pixel_height = p_h;
        unit_width = p_w;
        unit_height = p_h;
    }
    Space(int p_w, int p_h, double u_w, double u_h) : GameObject() {
        hit[0] = u_w;
        hit[1] = u_h;
        pixel_width = p_w;
        pixel_height = p_h;
        unit_width = u_w;
        unit_height = u_h;
    }
    virtual void setup() = 0;
};

#endif //FINAL_PROJECT_SPACE_HPP
