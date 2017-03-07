//
// Created by Brennan on 3/5/2017.
//

#ifndef FINAL_PROJECT_SPACE_HPP
#define FINAL_PROJECT_SPACE_HPP

#include "../game_object.hpp"
#include "../physics/constraints/constraint.hpp"
#include <unordered_map>
#include <string>

class Space : public GameObject {
protected:
    double unit_width;
    double unit_height;
    int pixel_width;
    int pixel_height;
public:

    static std::string TYPE;

    Space(int p_w, int p_h) : GameObject() {
        types.push_back(Space::TYPE);
        pixel_width = p_w;
        pixel_height = p_h;
        unit_width = p_w;
        unit_height = p_h;
    }
    Space(int p_w, int p_h, double u_w, double u_h) : GameObject() {
        types.push_back(Space::TYPE);
        pixel_width = p_w;
        pixel_height = p_h;
        unit_width = u_w;
        unit_height = u_h;
    }
    virtual void setup() = 0;
};

std::string Space::TYPE = "space";

#endif //FINAL_PROJECT_SPACE_HPP
