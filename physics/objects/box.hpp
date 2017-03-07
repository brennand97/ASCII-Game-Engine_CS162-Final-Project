//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_BOX_HPP
#define FINAL_PROJECT_BOX_HPP

#include "../particle_container.hpp"
#include "../constraints/constraint.hpp"

class Box : public ParticleContainer {
private:
    double width;
    double height;
public:
    Box(double * pos, double width, double height);
    double getWidth() { return width; }
    void setWidth(double w) { this->width = w; }
    double getHeight() { return height; }
    void setHeight(double h) { this->height = h; }
    void render();
};

#endif //FINAL_PROJECT_BOX_HPP
