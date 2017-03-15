//
// Created by Brennan on 3/5/2017.
//

#ifndef FINAL_PROJECT_SPACE_HPP
#define FINAL_PROJECT_SPACE_HPP

#include "../game_object.hpp"
#include "../physics/particle_container.hpp"
#include "../physics/constraints/box_constraint.hpp"
#include "../display/screen.hpp"
#include <string>
#include <vector>

class Space : public GameObject {
protected:
    double unit_width;
    double unit_height;
    ParticleContainer* physics;
    BoxConstraint* boundary;
    void handlePhysics(int);

public:

    static std::string TYPE;

    Space(double u_w, double u_h);
    ~Space();

    virtual void setup() = 0;

    double getWidth() { return unit_width; }
    double getHeight() { return unit_height; }

    void convertToPixels(double * pos, Screen* screen);
    double * convertToPixels(const double * pos, Screen* screen);
    double * convertToPixels(const double x, const double y, Screen* screen);
    void convertToPixels(double *x, double *y, Screen* screen);
    double * convertToPixels(Particle * p, Screen* screen);
};

#endif //FINAL_PROJECT_SPACE_HPP
