//
// Created by Brennan on 3/6/2017.
//

#include "box.hpp"
#include "../particle.hpp"
#include "../constraints/constraint.hpp"
#include "../constraints/line_constraint.hpp"
#include "../../spaces/space.hpp"
#include <string>
#include <cmath>

std::string Box::TYPE = "box";

Box::Box(double *pos, double width, double height) : ParticleContainer() {
    this->width = width;
    this->height = height;

    double * pos1 = new double[2];
    pos1[0] = 0;
    pos1[1] = 0;
    double * pos2 = new double[2];
    pos2[0] = width;
    pos2[1] = 0;
    double * pos3 = new double[2];
    pos3[0] = width;
    pos3[1] = - height;
    double * pos4 = new double[2];
    pos4[0] = 0;
    pos4[1] = - height;

    Particle* p1 = new Particle(pos1);
    Particle* p2 = new Particle(pos2);
    Particle* p3 = new Particle(pos3);
    Particle* p4 = new Particle(pos4);

    top_constraint = new LineConstraint(width, Constraint::Equality::EQUAL);
    top_constraint->addParticle(p1);
    top_constraint->addParticle(p2);

    bottom_constraint = new LineConstraint(width, Constraint::Equality::EQUAL);
    bottom_constraint->addParticle(p3);
    bottom_constraint->addParticle(p4);

    left_constraint = new LineConstraint(height, Constraint::Equality::EQUAL);
    left_constraint->addParticle(p1);
    left_constraint->addParticle(p4);

    right_constraint = new LineConstraint(height, Constraint::Equality::EQUAL);
    right_constraint->addParticle(p2);
    right_constraint->addParticle(p3);

    double diag = std::sqrt((width*width) + (height*height));
    diagonal_tl_br_constraint = new LineConstraint(diag, Constraint::Equality::EQUAL);
    diagonal_tl_br_constraint->addParticle(p1);
    diagonal_tl_br_constraint->addParticle(p3);

    diagonal_bl_tr_constraint = new LineConstraint(diag, Constraint::Equality::EQUAL);
    diagonal_bl_tr_constraint->addParticle(p2);
    diagonal_bl_tr_constraint->addParticle(p4);

    specific_constraints.push_back(top_constraint);
    specific_constraints.push_back(bottom_constraint);
    specific_constraints.push_back(left_constraint);
    specific_constraints.push_back(right_constraint);
    specific_constraints.push_back(diagonal_tl_br_constraint);
    specific_constraints.push_back(diagonal_bl_tr_constraint);
}

void Box::render() {
    Space* world = (Space*) getWorld();
}