//
// Created by Brennan on 3/7/2017.
//

#include "box_constraint.hpp"
#include <string>

std::string BoxConstraint::TYPE = "box_constraint";

BoxConstraint::BoxConstraint(double x, double y, double width, double height, double rigid) : SingleConstraint() {
    addType(BoxConstraint::TYPE);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->rigid = rigid;
}

BoxConstraint::BoxConstraint(int *pos, double width, double height, double rigid) : SingleConstraint() {
    addType(BoxConstraint::TYPE);
    if(pos != nullptr) {
        x = pos[0];
        y = pos[1];
    } else {
        x = 0;
        y = 0;
    }
    this->width = width;
    this->height = height;
    this->rigid = rigid;
}

void BoxConstraint::fix(int iter, Particle * p) {
    if((*p)[0] < x) {
        (*p)[0] -= ((*p)[0] - x) * rigid;
    } else if((*p)[0] > x + width) {
        (*p)[0] -= ((*p)[0] - (x + width)) * rigid;
    }
    if((*p)[1] < y) {
        (*p)[1] -= ((*p)[1] - y) * rigid;
    } else if((*p)[1] > y + height) {
        (*p)[1] -= ((*p)[1] - (y + height)) * rigid;
    }
}