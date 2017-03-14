//
// Created by Brennan on 3/12/2017.
//

#ifndef FINAL_PROJECT_WHEEL_HPP
#define FINAL_PROJECT_WHEEL_HPP

#include "../physics/particle_container.hpp"
#include "../physics/constraints/line_constraint.hpp"

class Wheel : public ParticleContainer {

    class WheelConstraint : public PairConstraint {
    private:
        double drag_coefficient;
    public:
        static std::string TYPE;

        WheelConstraint(double drag_coefficient);

        void fix(int, Particle*, Particle*);
    };

private:
    double wheel_width;
    double axel_width;
    double angle;
    double drag_coefficient;
    char draw_char = '#';

    LineConstraint* wheel_width_constraint;
    LineConstraint* axel_width_constraint;
    LineConstraint* positive_diagonal_constraint;
    LineConstraint* negative_diagonal_constraint;
    LineConstraint* attachment_constraint;

    Wheel::WheelConstraint* wheelConstraint;

public:

    static std::string TYPE;

    // Position defines center
    Wheel(double * pos, double width, double height, double angle, double drag_coefficient);

    double getAxelWidth() { return axel_width; }
    void setAxelWidth(double w);
    double getWheelWidth() { return wheel_width; }
    void setWheelWidth(double h);
    double getAngle() { return angle; }
    void setAngle(double angle);
    void changeAngle(double d_angle);
    char getDrawChar() { return draw_char; }
    void setDrawChar(char c) { this->draw_char = c; }

    void render(Screen*);

};

#endif //FINAL_PROJECT_WHEEL_HPP
