//
// Created by Brennan on 3/20/2017.
//

#include "key.hpp"
#include "../personal_utilities/vec_func.hpp"
#include "../space.hpp"

std::string Key::TYPE = "key";
std::string Key::KeyConstraint::TYPE = "key_constraint";

Key::Key(double *pos, double radius) : ParticleContainer() {
    addType(Key::TYPE);

    this->radius = radius;
    this->key_p = new Particle(douglas::vector::copy(pos));

    addChild(key_p);

    keyConstraint = new KeyConstraint(this);
    addSpecificConstraint(keyConstraint);

}

void Key::render(Screen *screen) {
    if(changed) {
        rendered_pixels.clear();

        if(!picked_up) {
            double *top_pos = douglas::vector::copy(key_p->getPosition());
            top_pos[1] += 10.0;
            double *middle_pos = douglas::vector::copy(key_p->getPosition());
            middle_pos[1] += 5.0;
            double *middle_left_pos = douglas::vector::copy(middle_pos);
            middle_left_pos[0] += 3.0;
            double *bottom_left_pos = douglas::vector::copy(key_p->getPosition());
            bottom_left_pos[0] += 3.0;
            double *bottom_pos = douglas::vector::copy(key_p->getPosition());

            Space *world = (Space *) getWorld();
            world->convertToPixels(top_pos, screen);
            world->convertToPixels(middle_pos, screen);
            world->convertToPixels(middle_left_pos, screen);
            world->convertToPixels(bottom_left_pos, screen);
            world->convertToPixels(bottom_pos, screen);

            screen->line(bottom_pos, top_pos, draw_char, &rendered_pixels);
            screen->line(middle_pos, middle_left_pos, draw_char, &rendered_pixels);
            screen->line(bottom_pos, bottom_left_pos, draw_char, &rendered_pixels);

            delete [] top_pos;
            delete [] middle_pos;
            delete [] middle_left_pos;
            delete [] bottom_left_pos;
            delete [] bottom_pos;
        }
    }

    screen->addToFrame(rendered_pixels);
}

Key::KeyConstraint::KeyConstraint(Key *key) : SingleConstraint() {
    addType(KeyConstraint::TYPE);
    this->key = key;
}

void Key::KeyConstraint::fix(int iter, Particle *p) {
    if(!this->key->picked_up) {
        double dist = douglas::vector::distance(p->getPosition(), this->key->key_p->getPosition());
        if (dist < this->key->radius) {
            this->key->setPickedUp(true);
        }
    }
}