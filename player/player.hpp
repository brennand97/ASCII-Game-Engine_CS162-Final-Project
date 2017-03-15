/**
 * Author:      Brennan Douglas
 * Date:        03/05/2017
 * Description: This is the header file for the Player class
 */

#ifndef FINAL_PROJECT_PLAYER_HPP
#define FINAL_PROJECT_PLAYER_HPP

#include "../physics/particle_container.hpp"
#include "wheel.hpp"

// Player is a car
class Player : public ParticleContainer {
private:

    char draw_char = '#';

    Wheel* frontWheels;
    Wheel* backWheels;

    LineConstraint* height_constraint;
    LineConstraint* diagonal_constraint;

public:

    static std::string TYPE;

    Player(double * pos,
           double width,
           double height,
           double wheel_width,
           double front_drag_coefficient,
           double back_drag_coefficient);

    double getWidth() { return frontWheels->getAxelWidth(); }
    void setWidth(double width) { frontWheels->setAxelWidth(width); backWheels->setAxelWidth(width); }
    double getHeight() { return height_constraint->getLength(); }
    void setHeight(double height) { height_constraint->setLength(height); }
    double getWheelWidth() { return frontWheels->getWheelWidth(); }
    void setWheelWidth(double width) { frontWheels->setWheelWidth(width); backWheels->setWheelWidth(width); }
    double getFrontWheelDrag() { return frontWheels->getDrag(); }
    void setFrontWheelDrag(double drag) { frontWheels->setDrag(drag); }
    double getBackWheelDrag() { return backWheels->getDrag(); }
    void setBackWheelDrag(double drag) { backWheels->setDrag(drag); }

    char getDrawChar() { return draw_char; }
    void setDrawChar(char c) { this->draw_char = c; frontWheels->setDrawChar(c); backWheels->setDrawChar(c); }

    void render(Screen* screen);

};

#endif //FINAL_PROJECT_PLAYER_HPP