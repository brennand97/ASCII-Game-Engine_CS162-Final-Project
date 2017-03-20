//
// Created by Brennan on 3/14/2017.
//

#include "player.hpp"
#include "../../space.hpp"

std::string Player::TYPE = "player_car";

Player::Player(double * pos,
               double width,
               double height,
               double wheel_width,
               double front_drag_coefficient,
               double back_drag_coefficient) : ParticleContainer() {

    addType(Player::TYPE);

    double x;
    double y_low;
    if ( pos != nullptr ) {
        x = pos[0];
        y_low = pos[1] - (height / 2.0);
    } else {
        x = width / 2.0;
        y_low = 0;
    }

    double * f_w_pos = douglas::vector::vector(x, y_low + height);
    frontWheels = new Wheel(f_w_pos, width, wheel_width, 0, front_drag_coefficient);
    frontWheels->setDrawChar(draw_char);
    addChild(frontWheels);
    delete [] f_w_pos;

    double * b_w_pos = douglas::vector::vector(x, y_low);
    backWheels = new Wheel(b_w_pos, width, wheel_width, 0, back_drag_coefficient);
    backWheels->setDrawChar(draw_char);
    addChild(backWheels);
    delete [] b_w_pos;

    height_constraint = new LineConstraint(height, Constraint::EQUAL);
    height_constraint->addParticle(((Particle*) frontWheels->getChildren()[1]));
    height_constraint->addParticle(((Particle*) backWheels->getChildren()[1]));
    height_constraint->addParticle(((Particle*) frontWheels->getChildren()[4]));
    height_constraint->addParticle(((Particle*) backWheels->getChildren()[4]));
    addSpecificConstraint(height_constraint);

    double diagonal = std::sqrt((width * width) + (height * height));
    diagonal_constraint = new LineConstraint(diagonal, Constraint::EQUAL);
    diagonal_constraint->addParticle(((Particle*) frontWheels->getChildren()[1]));
    diagonal_constraint->addParticle(((Particle*) backWheels->getChildren()[4]));
    diagonal_constraint->addParticle(((Particle*) frontWheels->getChildren()[4]));
    diagonal_constraint->addParticle(((Particle*) backWheels->getChildren()[1]));
    addSpecificConstraint(diagonal_constraint);

}

double* Player::getPlayerMidPoint() {
    double * intersect = douglas::vector::intersection(((Particle*) frontWheels->getChildren()[1])->getPosition(),
                                                       ((Particle*) backWheels->getChildren()[4])->getPosition(),
                                                       ((Particle*) frontWheels->getChildren()[4])->getPosition(),
                                                       ((Particle*) backWheels->getChildren()[1])->getPosition());
    return intersect;
}

void Player::movePlayerBy(double dx, double dy) {
    std::vector<GameObject*>::iterator g_it;
    std::vector<GameObject*> particles;
    getChildrenOfType(Particle::TYPE, &particles);
    for(g_it = particles.begin(); g_it != particles.end(); g_it++) {
        double * n_pos = douglas::vector::copy(((Particle*) *g_it)->getPosition());
        n_pos[0] += dx;
        n_pos[1] += dy;
        double * n_ppos = douglas::vector::copy(((Particle*) *g_it)->getPPosition());
        n_ppos[0] += dx;
        n_ppos[1] += dy;
        ((Particle*) *g_it)->setPosition(n_pos);
        ((Particle*) *g_it)->setPPosition(n_ppos);
        delete [] n_pos;
        delete [] n_ppos;
    }
}

void Player::render(Screen *screen) {

    renderChildren(screen);

    if(changed) {
        rendered_pixels.clear();

        double * front_diff = douglas::vector::subtract(((Particle*) frontWheels->getChildren()[4])->getPosition(),
                                                        ((Particle*) frontWheels->getChildren()[1])->getPosition());
        douglas::vector::scale(front_diff, 0.5);
        double * front_mid = douglas::vector::add(front_diff, ((Particle*) frontWheels->getChildren()[1])->getPosition());


        double * back_diff = douglas::vector::subtract(((Particle*) backWheels->getChildren()[4])->getPosition(),
                                                       ((Particle*) backWheels->getChildren()[1])->getPosition());
        douglas::vector::scale(back_diff, 0.5);
        double * back_mid = douglas::vector::add(back_diff, ((Particle*) backWheels->getChildren()[1])->getPosition());

        douglas::vector::scale(back_diff, 0.5);
        double * back_l_mid = douglas::vector::add(back_diff, back_mid);
        douglas::vector::scale(back_diff, -1.0);
        double * back_r_mid = douglas::vector::add(back_diff, back_mid);

        Space* space = (Space*) getWorld();
        space->convertToPixels(front_mid, screen);
        space->convertToPixels(back_mid, screen);
        space->convertToPixels(back_l_mid, screen);
        space->convertToPixels(back_r_mid, screen);

        screen->line(front_mid, back_mid, draw_char, &rendered_pixels);
        screen->line(front_mid, back_l_mid, draw_char, &rendered_pixels);
        screen->line(front_mid, back_r_mid, draw_char, &rendered_pixels);

        delete [] front_mid;
        delete [] front_diff;
        delete [] back_mid;
        delete [] back_diff;
        delete [] back_l_mid;
        delete [] back_r_mid;

    }

    screen->addToFrame(rendered_pixels);

}