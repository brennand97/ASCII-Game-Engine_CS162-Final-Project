/**
 * Author:      Brennan Douglas
 * Date:        03/13/2017
 * Description: This file holds the source code for the car class
 */

#include "player.hpp"
#include "../../space.hpp"

std::string Player::TYPE = "player_car";

// Default player constructor.
// <pos> refers to the center position of the player
// <width> is the width of the player (car)
// <height> is the length of the player (car)
// <wheel_width> is the width of the front and back wheel of the player (car)
// <front_drag_coefficient> is the drag coefficient for the front wheel's
//                          WheelConstraint (e.g. the sideways friction of the wheels)
// <back_drag_coefficient> is the same as front_drag_coefficient except for the back wheels
Player::Player(double * pos,
               double width,
               double height,
               double wheel_width,
               double front_drag_coefficient,
               double back_drag_coefficient) : ParticleContainer() {

    // Add type to Typed type list
    addType(Player::TYPE);

    // Calculate the bottom middle point for the car box
    double x;
    double y_low;
    if ( pos != nullptr ) {
        x = pos[0];
        y_low = pos[1] - (height / 2.0);
    } else {
        x = width / 2.0;
        y_low = 0;
    }

    // Create the front wheels
    double * f_w_pos = douglas::vector::vector(x, y_low + height);
    frontWheels = new Wheel(f_w_pos, width, wheel_width, 0, front_drag_coefficient);
    frontWheels->setDrawChar(draw_char);
    addChild(frontWheels);
    delete [] f_w_pos;

    // Create the back wheels
    double * b_w_pos = douglas::vector::vector(x, y_low);
    backWheels = new Wheel(b_w_pos, width, wheel_width, 0, back_drag_coefficient);
    backWheels->setDrawChar(draw_char);
    addChild(backWheels);
    delete [] b_w_pos;

    // Define the line constraint for the height of the car
    height_constraint = new LineConstraint(height, Constraint::EQUAL);
    height_constraint->addParticle(((Particle*) frontWheels->getChildren()[1]));
    height_constraint->addParticle(((Particle*) backWheels->getChildren()[1]));
    height_constraint->addParticle(((Particle*) frontWheels->getChildren()[4]));
    height_constraint->addParticle(((Particle*) backWheels->getChildren()[4]));
    addSpecificConstraint(height_constraint);

    // Define the line constraint for the diagonals of the car
    double diagonal = std::sqrt((width * width) + (height * height));
    diagonal_constraint = new LineConstraint(diagonal, Constraint::EQUAL);
    diagonal_constraint->addParticle(((Particle*) frontWheels->getChildren()[1]));
    diagonal_constraint->addParticle(((Particle*) backWheels->getChildren()[4]));
    diagonal_constraint->addParticle(((Particle*) frontWheels->getChildren()[4]));
    diagonal_constraint->addParticle(((Particle*) backWheels->getChildren()[1]));
    addSpecificConstraint(diagonal_constraint);

    // The width constraint doesn't need to be defined as that is taken care of by the front and back wheels.

}

// Return the middle of the player.  This function assumes that the car is in a good state due to its constraints
// as the midpoint is calculated by the intersection of the diagonal lines made by the midpoints of the front and back
// wheels of the player (car).
double* Player::getPlayerMidPoint() {
    double * intersect = douglas::vector::intersection(((Particle*) frontWheels->getChildren()[1])->getPosition(),
                                                       ((Particle*) backWheels->getChildren()[4])->getPosition(),
                                                       ((Particle*) frontWheels->getChildren()[4])->getPosition(),
                                                       ((Particle*) backWheels->getChildren()[1])->getPosition());
    return intersect;
}

// Move all the particles in the player by dx and dy.  This is used for jumping between Rooms.
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

// Render function for the car.  Renders only the middle connecting lines of the car between the front and back
// wheels as the front and back wheels render themselves.  The render consists of a straight line between the centers
// of the wheels and two diagonal lines forming a triangle pointing to the front wheels to make moving the car
// easier as it provides the user with a visual of which end of the player (car) is the front before they turn the
// wheels.
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