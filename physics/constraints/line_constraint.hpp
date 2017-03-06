//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_LINE_CONSTRAINT_HPP
#define FINAL_PROJECT_LINE_CONSTRAINT_HPP

#include "constraint.hpp"
#include <cmath>

template <double LENGTH, Constraint::Equality EQ>
class LineConstraint : public Constraint {
public:
    void LineConstraint::fix(Particle *p1, Particle *p2) {
        double s_d = Constraint::sqr_dist(p1, p2);
        double delta = LENGTH - std::sqrt(s_d);
        switch (EQ) {
            case EQUAL: {
                if (delta == 0) {
                    return;
                }
                break;
            }
            case LESS_THAN | LESS_THAN_EQUAL: {
                if (delta > 0) {
                    return;
                }
                break;
            }
            case GREATER_THAN | GREATER_THAN_EQUAL: {
                if (delta < 0) {
                    return;
                }
                break;
            }
        }
        double x_d = (p2[0] - p1[0]);
        double y_d = (p2[1] - p1[1]);
        double mass_ratio = p1->getMass() / p2->getMass();
        double dx1 = (mass_ratio + 1) / x_d;
        double dx2 = -1 * (mass_ratio * dx1);
        double dy1 = (mass_ratio + 1) / y_d;
        double dy2 = -1 * (mass_ratio * dy1);
        p1[0] += dx1;
        p1[1] += dy1;
        p2[0] += dx2;
        p2[0] += dy2;
    }
};

#endif //FINAL_PROJECT_LINE_CONSTRAINT_HPP
