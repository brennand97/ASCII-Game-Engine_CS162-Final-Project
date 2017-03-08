//
// Created by Brennan on 3/6/2017.
//

#include "box.hpp"
#include "../particle.hpp"
#include "../../spaces/space.hpp"
#include <string>
#include <cmath>
#include <algorithm>

std::string Box::TYPE = "box";

Box::Box(double *pos, double width, double height) : ParticleContainer() {
    addType(Box::TYPE);

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

    addChild(p1);
    addChild(p2);
    addChild(p3);
    addChild(p4);

    width_constraint = new LineConstraint(width, Constraint::Equality::EQUAL);
    width_constraint->addParticle(p1);
    width_constraint->addParticle(p2);
    width_constraint->addParticle(p3);
    width_constraint->addParticle(p4);

    height_constraint = new LineConstraint(height, Constraint::Equality::EQUAL);
    height_constraint->addParticle(p1);
    height_constraint->addParticle(p4);
    height_constraint->addParticle(p2);
    height_constraint->addParticle(p3);

    double diag = std::sqrt((width*width) + (height*height));
    diagonal_constraint = new LineConstraint(diag, Constraint::Equality::EQUAL);
    diagonal_constraint->addParticle(p1);
    diagonal_constraint->addParticle(p3);
    diagonal_constraint->addParticle(p2);
    diagonal_constraint->addParticle(p4);

    specific_constraints.push_back(width_constraint);
    specific_constraints.push_back(height_constraint);
    specific_constraints.push_back(diagonal_constraint);
}

Box::~Box() {
    delete width_constraint;
    delete height_constraint;
    delete diagonal_constraint;
}

void Box::render() {
    Space* world = (Space*) getWorld();

    double rasterization_tolerence = 0.01;
    double u_p_p = world->getUnitsPerPixel();



}