//
// Created by Brennan on 3/5/2017.
//

#ifndef FINAL_PROJECT_SPACE_HPP
#define FINAL_PROJECT_SPACE_HPP

#include "../game_object.hpp"
#include "../physics/particle_container.hpp"
#include <string>

class Space : public GameObject {
protected:
    double unit_width;
    double unit_height;
    int pixel_width;
    int pixel_height;
    ParticleContainer* physics;
public:

    static std::string TYPE;

    Space(int p_w, int p_h);
    Space(int p_w, int p_h, double u_w, double u_h);

    virtual void setup() = 0;
};

#endif //FINAL_PROJECT_SPACE_HPP
