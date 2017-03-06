//
// Created by Brennan on 3/6/2017.
//

#include "drag_constraint.hpp"
#include <iostream>
#include <cmath>

DragConstraint::DragConstraint(double drag) : Constraint(Constraint::LINK::SINGLE) {
    this->drag = drag;
}

void DragConstraint::applyDrag(Particle &p) {
    double p_dt = p.getPreviousStepTime();
    const double * ppos = p.getPPosition();
    double v_x = (p[0] - ppos[0]) / p_dt;
    double v_y = (p[1] - ppos[1]) / p_dt;
    if (std::abs(v_x) < 0.00001) {
        //p[0] = ppos[0];
        return;
    } else if (std::abs(v_y) < 0.00001) {
        //p[1] = ppos[1];
        return;
    }
    double ax = (v_x / std::abs(v_x)) * (v_x * v_x) * (drag / p.getMass());
    double ay = (v_y / std::abs(v_y)) * (v_y * v_y) * (drag / p.getMass());
    std::cout << v_x << ", " << ax << ", " << ax * (p_dt * p_dt) << std::endl;
    std::cout << v_y << ", " << ay << ", " << ay * (p_dt * p_dt) << std::endl;
    p[0] -= ax * (p_dt * p_dt);
    p[1] -= ay * (p_dt * p_dt);
}

void DragConstraint::fix(Particle &p1, Particle &p2) {
    if(&p1 != nullptr) {
        applyDrag(p1);
    }
    if(&p2 != nullptr) {
        applyDrag(p2);
    }
}