//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_BOX_HPP
#define FINAL_PROJECT_BOX_HPP

#include "../objects/convex_polygon.hpp"
#include "../constraints/line_constraint.hpp"
#include <string>

class Box : public ConvexPolygon {
private:
    double width;
    double height;
//    LineConstraint* width_constraint;
//    LineConstraint* height_constraint;
//    LineConstraint* diagonal_constraint;
public:

    static std::string TYPE;

    Box(double * pos, double width, double height);
    ~Box();

    double getWidth() { return width; }
    //void setWidth(double w) { this->width = w; }
    double getHeight() { return height; }
    //void setHeight(double h) { this->height = h; }

    //void render(Screen*);
};

#endif //FINAL_PROJECT_BOX_HPP
