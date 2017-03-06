//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_BOX_HPP
#define FINAL_PROJECT_BOX_HPP

#include "../game_object.hpp"
#include "../physics/constraints/constraint.hpp"

class Box : public GameObject {
private:
    double width;
    double height;
public:
    Box(double * pos, double width, double height);
    double getWidth() { return width; }
    void setWidth(double w) {
        this->width = w;
        hit[0] = w;
    }
    double getHeight() { return height; }
    void setHeight(double h) {
        this->height = h;
        hit[1] = h;
    }
    void render();
};

#endif //FINAL_PROJECT_BOX_HPP
