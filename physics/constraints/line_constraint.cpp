//
// Created by Brennan on 3/6/2017.
//

#include "line_constraint.hpp"
#include <stdexcept>

LineConstraint::LineConstraint(double length, Constraint::Equality eq) : Constraint(Constraint::LINK::PAIR) {
    this->length = length;
    this->eq = eq;
}

void LineConstraint::fix() {
    if(particles.size() % 2 != 0) {
        throw std::invalid_argument("There are not an even number of particles, there is an incomplete particle pair.");
    } else {
        for(unsigned int i = 0; i < particles.size(); i+=2) {
            for(int j = 0; j < 2; j++) {
                while ((i + j) < particles.size() && particles[i + j] == nullptr) {
                    particles.erase(particles.begin() + i + j, particles.begin() + i + j + 1);
                }
            }
            if(i + 1 < particles.size()) {
                fix(particles[i], particles[i+1]);
            }
        }
    }
}

void LineConstraint::fix(Particle *p1, Particle *p2) {
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
    double x_d = ((*p1)[0] - (*p2)[0]);
    double y_d = ((*p1)[1] - (*p2)[1]);
    double angle = std::atan2(y_d, x_d);
    if(x_d != 0) x_d = (std::cos(angle) * length) - x_d;
    if(y_d != 0) y_d = (std::sin(angle) * length) - y_d;
    double mass_ratio = p1->getMass() / p2->getMass();
    double dx1 = x_d / (mass_ratio + 1);
    double dx2 = -1 * (mass_ratio * dx1);
    double dy1 = y_d / (mass_ratio + 1);
    double dy2 = -1 * (mass_ratio * dy1);
    (*p1)[0] += dx1;
    (*p1)[1] += dy1;
    (*p2)[0] += dx2;
    (*p2)[0] += dy2;
}