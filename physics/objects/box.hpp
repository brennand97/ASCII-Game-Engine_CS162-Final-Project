//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_BOX_HPP
#define FINAL_PROJECT_BOX_HPP

#include "../particle_container.hpp"
#include "../constraints/line_constraint.hpp"
#include <string>

class Box : public ParticleContainer {
private:
    double width;
    double height;
    LineConstraint* top_constraint;
    LineConstraint* bottom_constraint;
    LineConstraint* left_constraint;
    LineConstraint* right_constraint;
    LineConstraint* diagonal_tl_br_constraint;
    LineConstraint* diagonal_bl_tr_constraint;
public:

    static std::string TYPE;

    Box(double * pos, double width, double height);
    double getWidth() { return width; }
    void setWidth(double w) { this->width = w; }
    double getHeight() { return height; }
    void setHeight(double h) { this->height = h; }
    void render();
};

#endif //FINAL_PROJECT_BOX_HPP
