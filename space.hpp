//
// Created by Brennan on 3/5/2017.
//

#ifndef FINAL_PROJECT_SPACE_HPP
#define FINAL_PROJECT_SPACE_HPP

#include "game_object.hpp"
#include "physics/particle_container.hpp"
#include "physics/constraints/box_constraint.hpp"
#include "display/screen.hpp"
#include <string>
#include <vector>

class Space : public GameObject {
protected:
    double unit_width;
    double unit_height;
    ParticleContainer* physics;
    BoxConstraint* boundary;
    void handlePhysics(int);

    Space* neighbors[4];

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

    ParticleContainer* getPhysics() { return physics; }

    void newChild(GameObject* child);

    // Handle neighbor getting and setting
    // Indexed starting from the top (0) going clockwise until the left (3)
    Space* getSpace(int index) { return neighbors[index]; }
    void setSpace(int index, Space* space) { neighbors[index] = space; }
};

#endif //FINAL_PROJECT_SPACE_HPP
