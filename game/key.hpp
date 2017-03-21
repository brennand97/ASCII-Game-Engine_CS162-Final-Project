//
// Created by Brennan on 3/20/2017.
//

#ifndef FINAL_PROJECT_KEY_HPP
#define FINAL_PROJECT_KEY_HPP

#include "../physics/particle_container.hpp"
#include "../physics/constraints/single_constraint.hpp"

class Key : public ParticleContainer {
public:
    class KeyConstraint : public SingleConstraint {
    protected:
        Key* key;
    public:
        static std::string TYPE;
        KeyConstraint(Key* key);
        void fix(int iter, Particle* p);
    };

protected:
    Particle* key_p;
    double radius;
    bool picked_up = false;
    KeyConstraint* keyConstraint;

public:
    static std::string TYPE;

    Key(double * pos, double radius);

    double getRadius() { return radius; }
    void setRadius(double d) { this->radius = radius; }
    bool getPickedUp() { return picked_up; }
    void setPickedUp(bool b) { this->picked_up = b; }
    KeyConstraint* getKeyConstraint() { return keyConstraint; }

    void render(Screen* screen);
};

#endif //FINAL_PROJECT_KEY_HPP
