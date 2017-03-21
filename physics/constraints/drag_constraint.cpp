/**
 * Author:      Brennan Douglas
 * Date:        03/06/2017
 * Description: This is the source file for the DragConstraint class
 */

#include "drag_constraint.hpp"
#include <string>
#include <cmath>

std::string DragConstraint::TYPE = "drag_constraint";

// Constructor for DragConstraint
// <drag> is the coefficient multiplied by the square of the velocity to determine how much the particle will be
//        slowed down.
DragConstraint::DragConstraint(double drag) : SingleConstraint() {
    addType(DragConstraint::TYPE);
    this->drag = drag;
}

// This is the method that applies the speed limitation
void DragConstraint::fix(int iter, Particle *p) {
    if(iter > 1) {
        return;
    }
    double p_dt = p->getPreviousStepTime();
    const double * ppos = p->getPPosition();
    double v_x = ((*p)[0] - ppos[0]) / p_dt;
    double v_y = ((*p)[1] - ppos[1]) / p_dt;
    if (std::abs(v_x) < 0.00001) {
        return;
    } else if (std::abs(v_y) < 0.00001) {
        return;
    }
    double ax = (v_x / std::abs(v_x)) * (v_x * v_x) * (drag / p->getMass());
    double ay = (v_y / std::abs(v_y)) * (v_y * v_y) * (drag / p->getMass());
    (*p)[0] -= ax * (p_dt * p_dt);
    (*p)[1] -= ay * (p_dt * p_dt);
}