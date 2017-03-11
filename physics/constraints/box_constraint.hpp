//
// Created by Brennan on 3/7/2017.
//

#ifndef FINAL_PROJECT_BOX_CONSTRAINT_HPP
#define FINAL_PROJECT_BOX_CONSTRAINT_HPP

#include "single_constraint.hpp"
#include <string>

class BoxConstraint : public SingleConstraint {
protected:
    double x;
    double y;
    double width;
    double height;
    double rigid;
public:

    static std::string TYPE;

    BoxConstraint(double x, double y, double width, double height, double rigid);
    BoxConstraint(int* pos, double width, double height, double rigid);

    double getX() { return x; }
    void setX(double x) { this->x = x; }
    double getY() { return y; }
    void setY(double y) { this->y = y; }
    double getWidth() { return width; }
    void setWidth(double width) { this->width = width; }
    double getHeight() { return height; }
    void setHeight(double height) { this->height = height; }
    double getRigid() { return rigid; }
    void setRigid(double rigid) { this->rigid = rigid; }

    void fix(int, Particle*);

};

#endif //FINAL_PROJECT_BOX_CONSTRAINT_HPP
