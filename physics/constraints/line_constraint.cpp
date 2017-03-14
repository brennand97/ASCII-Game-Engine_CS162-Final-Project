//
// Created by Brennan on 3/6/2017.
//

#include "line_constraint.hpp"
#include <stdexcept>
#include <string>

std::string LineConstraint::TYPE = "line_constraint";

LineConstraint::LineConstraint(double length, Constraint::Equality eq) : PairConstraint() {
    addType(LineConstraint::TYPE);
    this->length = length;
    this->eq = eq;
}

void LineConstraint::fix(int iter, Particle *p1, Particle *p2) {
    double s_d = Constraint::sqr_dist(p1, p2);
    double delta = length - std::sqrt(s_d);
    switch (eq) {
        case EQUAL: {
            if (delta == 0) {
                return;
            }
            break;
        }
        case LESS_THAN:
        case LESS_THAN_EQUAL: {
            if (delta > 0) {
                return;
            }
            break;
        }
        case GREATER_THAN:
        case GREATER_THAN_EQUAL: {
            if (delta < 0) {
                return;
            }
            break;
        }
    }

    double dx = (*p2)[0] - (*p1)[0];
    double dy = (*p2)[1] - (*p1)[1];

    double dlength = std::sqrt((dx * dx) + (dy * dy));

    double diff = (dlength - length) / dlength;

    double mass_ratio = p1->getMass() / p2->getMass();
    double scale1 = 1 / (1 + mass_ratio);
    double scale2 = scale1 * mass_ratio;

    (*p1)[0] += dx * scale1 * diff;
    (*p1)[1] += dy * scale1 * diff;
    (*p2)[0] -= dx * scale2 * diff;
    (*p2)[1] -= dy * scale2 * diff;

}