//
// Created by Brennan on 3/7/2017.
//

#include "bouncy_box_constraint.hpp"
#include <string>

std::string BouncyBoxConstraint::TYPE = "bouncy_box_constraint";

BouncyBoxConstraint::BouncyBoxConstraint(double x, double y, double width, double height) : SingleConstraint() {
    addType(BouncyBoxConstraint::TYPE);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

BouncyBoxConstraint::BouncyBoxConstraint(int *pos, double width, double height) : SingleConstraint() {
    addType(BouncyBoxConstraint::TYPE);
    if(pos != nullptr) {
        x = pos[0];
        y = pos[1];
    } else {
        x = 0;
        y = 0;
    }
    this->width = width;
    this->height = height;
}

void BouncyBoxConstraint::fix(int iter, Particle * p) {
    if((*p)[0] < x) {

        double dx = (*p)[0] - x;
        double v_dx = (*p)[0] - p->getPPosition()[0];
        double v_dy = (*p)[1] - p->getPPosition()[1];

        double * n_ppos = new double[2];
        n_ppos[0] = -p->getPPosition()[0];
        n_ppos[1] = p->getPPosition()[1];

        (*p)[0] *= -1;
        p->setPPosition(n_ppos);

    } else if((*p)[0] > x + width) {
        (*p)[0] -= (*p)[0] - (x + width);
    }
    if((*p)[1] < y) {
        (*p)[1] -= (*p)[1] - y;
    } else if((*p)[1] > y + height) {
        (*p)[1] -= (*p)[1] - (y + height);
    }
}