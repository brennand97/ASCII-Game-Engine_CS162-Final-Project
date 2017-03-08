//
// Created by Brennan on 3/5/2017.
//

#ifndef FINAL_PROJECT_SPACE_HPP
#define FINAL_PROJECT_SPACE_HPP

#include "../game_object.hpp"
#include "../physics/particle_container.hpp"
#include "../physics/constraints/box_constraint.hpp"
#include <string>
#include <vector>

class Space : public GameObject {
protected:
    double unit_width;
    double unit_height;
    int pixel_width;
    int pixel_height;
    char** frame;
    ParticleContainer* physics;
    BoxConstraint* boundary;
    void handlePhysics(int);
public:

    static std::string TYPE;

    Space(int p_w, int p_h);
    Space(int p_w, int p_h, double u_w, double u_h);
    ~Space();

    virtual void setup() = 0;

    int getPixelWidth() { return pixel_width; }
    int getPixelHeight() { return pixel_height; }
    double getUnitWidth() { return unit_width; }
    double getUnitHeight() { return unit_height; }

    double getXUnitsPerPixel();
    double getYUnitsPerPixel();
    double getUnitsPerPixel();
};

#endif //FINAL_PROJECT_SPACE_HPP
