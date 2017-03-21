//
// Created by Brennan on 3/7/2017.
//

#include "box_constraint.hpp"
#include <string>

std::string BoxConstraint::TYPE = "box_constraint";

// Default constructor for the BoxConstraint
// <x> is the bottom left x-cord of the constraint
// <y> is the bottom left y-cord of the constraint
// <width> is the width of the box
// <height> is the height of the box
// <rigid> is a double between 0 and 1 that determines how much of a particles displacement is pushed back
BoxConstraint::BoxConstraint(double x, double y, double width, double height, double rigid) : SingleConstraint() {
    addType(BoxConstraint::TYPE);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->rigid = rigid;
}

// Same as above with x, y replaced by a 2-d array representing a vector
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

// Function tha applies the constraints law to all particles effected
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