//
// Created by Brennan on 3/12/2017.
//

#include "wheel.hpp"
#include <cmath>
#include "../spaces/space.hpp"

std::string Wheel::TYPE = "wheel";
std::string Wheel::WheelConstraint::TYPE = "wheel_constraint";

Wheel::Wheel(double *pos, double width, double height, double angle, double drag_coefficient) : ParticleContainer() {
    addType(Wheel::TYPE);

    this->wheel_width = height;
    this->axel_width = width;
    this->drag_coefficient = drag_coefficient;
    this->angle = angle;

    // Left most x
    double l_x;
    // Bottom most y
    double b_y;

    if(pos != nullptr) {
        l_x = pos[0] - (width / 2.0);
        b_y = pos[1] - (height / 2.0);
    } else {
        l_x = 0;
        b_y = 0;
    }

    // Left wheel top
    double * l_w_t_pos = new double[2];
    l_w_t_pos[0] = l_x;
    l_w_t_pos[1] = b_y + height;
    // Left wheel bottom
    double * l_w_b_pos = new double[2];
    l_w_b_pos[0] = l_x;
    l_w_b_pos[1] = b_y;
    // Left wheel attachment
    double * l_w_a_pos = new double[2];
    l_w_a_pos[0] = l_x;
    l_w_a_pos[1] = b_y + (height / 2);
    // Right wheel top
    double * r_w_t_pos = new double[2];
    r_w_t_pos[0] = l_x + width;
    r_w_t_pos[1] = b_y + height;
    // Right wheel bottom
    double * r_w_b_pos = new double[2];
    r_w_b_pos[0] = l_x + width;
    r_w_b_pos[1] = b_y;
    // Right wheel attachment
    double * r_w_a_pos = new double[2];
    r_w_a_pos[0] = l_x + width;
    r_w_a_pos[1] = b_y + (height / 2);

    // Particles, same naming convention as above
    Particle* l_w_t = new Particle(l_w_t_pos);
    Particle* l_w_b = new Particle(l_w_b_pos);
    Particle* l_w_a = new Particle(l_w_a_pos);
    l_w_a->setMass(10);
    Particle* r_w_t = new Particle(r_w_t_pos);
    Particle* r_w_b = new Particle(r_w_b_pos);
    Particle* r_w_a = new Particle(r_w_a_pos);
    r_w_a->setMass(10);

    // Add particles as children (left -> right, top -> bottom)
    addChild(l_w_t);
    addChild(l_w_a);
    addChild(l_w_b);
    addChild(r_w_t);
    addChild(r_w_a);
    addChild(r_w_b);

    wheel_width_constraint = new LineConstraint(height, Constraint::EQUAL);
    wheel_width_constraint->addParticle(l_w_t);
    wheel_width_constraint->addParticle(l_w_b);
    wheel_width_constraint->addParticle(r_w_t);
    wheel_width_constraint->addParticle(r_w_b);
    addSpecificConstraint(wheel_width_constraint);

    axel_width_constraint = new LineConstraint(width, Constraint::EQUAL);
    axel_width_constraint->addParticle(l_w_t);
    axel_width_constraint->addParticle(r_w_t);
    axel_width_constraint->addParticle(l_w_b);
    axel_width_constraint->addParticle(r_w_b);
    addSpecificConstraint(axel_width_constraint);

    attachment_constraint = new LineConstraint(height / 2, Constraint::EQUAL);
    attachment_constraint->addParticle(l_w_a);
    attachment_constraint->addParticle(l_w_t);
    attachment_constraint->addParticle(l_w_a);
    attachment_constraint->addParticle(l_w_b);
    attachment_constraint->addParticle(r_w_a);
    attachment_constraint->addParticle(r_w_t);
    attachment_constraint->addParticle(r_w_a);
    attachment_constraint->addParticle(r_w_b);
    addSpecificConstraint(attachment_constraint);

    double diagonal = std::sqrt((width * width) + (height * height));

    positive_diagonal_constraint = new LineConstraint(diagonal, Constraint::EQUAL);
    positive_diagonal_constraint->addParticle(l_w_b);
    positive_diagonal_constraint->addParticle(r_w_t);
    addSpecificConstraint(positive_diagonal_constraint);

    negative_diagonal_constraint = new LineConstraint(diagonal, Constraint::EQUAL);
    negative_diagonal_constraint->addParticle(l_w_t);
    negative_diagonal_constraint->addParticle(r_w_b);
    addSpecificConstraint(negative_diagonal_constraint);

    wheelConstraint = new WheelConstraint(this->drag_coefficient);
    wheelConstraint->addParticle(l_w_t);
    wheelConstraint->addParticle(l_w_b);
    wheelConstraint->addParticle(r_w_t);
    wheelConstraint->addParticle(r_w_b);
    addSpecificConstraint(wheelConstraint);

    setAngle(angle);

    for(int i = 0; i < 5; i++) {
        ((PairConstraint*) wheel_width_constraint)->fix(i + 1);
        ((PairConstraint*) axel_width_constraint)->fix(i + 1);
        ((PairConstraint*) attachment_constraint)->fix(i + 1);
        ((PairConstraint*) positive_diagonal_constraint)->fix(i + 1);
        ((PairConstraint*) negative_diagonal_constraint)->fix(i + 1);
    }

    for(GameObject* go: children) {
        ((Particle*) go)->setPPosition(((Particle*) go)->getPosition());
    }

}

void Wheel::setAxelWidth(double w) {
    axel_width = w;
    axel_width_constraint->setLength(axel_width);
    double diagonal = std::sqrt((axel_width * axel_width) + (wheel_width * wheel_width));
    positive_diagonal_constraint->setLength(diagonal);
    negative_diagonal_constraint->setLength(diagonal);
    setAngle(angle);
}

void Wheel::setWheelWidth(double h) {
    wheel_width = h;
    wheel_width_constraint->setLength(wheel_width);
    double diagonal = std::sqrt((axel_width * axel_width) + (wheel_width * wheel_width));
    attachment_constraint->setLength(wheel_width / 2);
    positive_diagonal_constraint->setLength(diagonal);
    negative_diagonal_constraint->setLength(diagonal);
    setAngle(angle);
}

void Wheel::setAngle(double angle) {
    const double pi = 3.1415926535897;

    double a_sign = (angle < 0 ? -1 : 1);

    this->angle = angle;
    double pid4 = pi / 4;
    if (angle < -pid4 || angle > pid4) {
        angle = pid4 * a_sign;
    }
    double displacement = std::sin(angle) * wheel_width;
    double height = std::cos(angle) * wheel_width;
    double p_diagonal, n_diagonal;

    // Update constraints
    double width = axel_width + ( 2.0 * displacement );
    p_diagonal = std::sqrt((width * width) + (height * height));
    width = axel_width - ( 2.0 * displacement );
    n_diagonal = std::sqrt((width * width) + (height * height));
    positive_diagonal_constraint->setLength(p_diagonal);
    negative_diagonal_constraint->setLength(n_diagonal);

    last_angle_change = std::chrono::high_resolution_clock::now();
}

void Wheel::changeAngle(double d_angle) {
    angle += d_angle;
    setAngle(angle);
}

double* Wheel::getWheelVector() {
    return douglas::vector::subtract(((Particle*) children[0])->getPosition(),
                                     ((Particle*) children[1])->getPosition());
}

void Wheel::render(Screen * screen) {
    Space* world = (Space*) getWorld();
    std::vector<Pixel> lines;
    double * p0 = world->convertToPixels((Particle*) getChildren()[0], screen);
    double * p1 = world->convertToPixels((Particle*) getChildren()[1], screen);
    double * p2 = world->convertToPixels((Particle*) getChildren()[2], screen);
    double * p3 = world->convertToPixels((Particle*) getChildren()[3], screen);
    double * p4 = world->convertToPixels((Particle*) getChildren()[4], screen);
    double * p5 = world->convertToPixels((Particle*) getChildren()[5], screen);
    screen->line(p1, p4, draw_char, &lines);
    screen->line(p0, p2, draw_char, &lines);
    screen->line(p3, p5, draw_char, &lines);
    screen->addToFrame(lines);
    delete [] p0;
    delete [] p1;
    delete [] p2;
    delete [] p3;
    delete [] p4;
    delete [] p5;
}

void Wheel::step(double dt) {
    ParticleContainer::step(dt);
    if((std::chrono::high_resolution_clock::now() - last_angle_change).count() / 1000000 > hold_angle_milliseconds) {
        setAngle(0);
    }
}

Wheel::WheelConstraint::WheelConstraint(double drag_coefficient) {
    addType(WheelConstraint::TYPE);
    this->drag_coefficient = drag_coefficient;
}

void Wheel::WheelConstraint::fix(int iter, Particle * p1, Particle * p2) {

    // Only apply constraint on the first iteration
    if ( iter < 2 ) {
        // Calculate the two velocities
        double *vel1 = douglas::vector::subtract(p1->getPosition(), p1->getPPosition());
        double *vel2 = douglas::vector::subtract(p2->getPosition(), p2->getPPosition());

        // Calculate the vector along the wheel
        double *wheelVector = douglas::vector::subtract(p1->getPosition(), p2->getPosition());
        // Calculate the vector orthogonal to the wheel
        double *resistanceVector = douglas::vector::vector(-wheelVector[1], wheelVector[0]);

        // Calculate the amount of velocity parallel to the resistance vector
        double *res_vel1 = douglas::vector::project(vel1, resistanceVector);
        double *res_vel2 = douglas::vector::project(vel2, resistanceVector);

        if (douglas::vector::magnitude(res_vel1) != 0) {
            // Tmp container for calculations
            double * tmp = douglas::vector::copy(res_vel1);
            // Square each of the components
            tmp[0] *= std::abs(res_vel1[0]);
            tmp[1] *= std::abs(res_vel1[1]);
            // Get the previous delta time for the particle
            double p_dt = p1->getPreviousStepTime();
            // Scale the factor by the drag coefficient, time squared, and inverse mass to get displacement
            douglas::vector::scale(tmp, (this->drag_coefficient * p_dt) / p1->getMass());
            // Reverse vector to be opposite of velocity
            douglas::vector::scale(tmp, -1.0);
            // Calculate the new position
            double *diff = douglas::vector::project(tmp, resistanceVector);
            if(douglas::vector::magnitude(diff) > douglas::vector::magnitude(res_vel1)) {
                douglas::vector::scale(res_vel1, -1.0);
                double *n_pos = douglas::vector::add(p1->getPosition(), res_vel1);
                // Set the new position
                p1->setPosition(n_pos);
                // Delete all the old variables
                delete [] n_pos;
            } else {
                double *n_pos = douglas::vector::add(p1->getPosition(), diff);
                // Set the new position
                p1->setPosition(n_pos);
                // Delete all the old variables
                delete [] n_pos;
            }
            delete [] tmp;
            delete [] diff;
        }
        if (douglas::vector::magnitude(res_vel2) != 0) {
            // Tmp container for calculations
            double * tmp = douglas::vector::copy(res_vel2);
            // Square each of the components
            tmp[0] *= std::abs(res_vel2[0]);
            tmp[1] *= std::abs(res_vel2[1]);
            // Get the previous delta time for the particle
            double p_dt = p2->getPreviousStepTime();
            // Scale the factor by the drag coefficient, time squared, and inverse mass to get displacement
            douglas::vector::scale(tmp, (this->drag_coefficient * p_dt) / p2->getMass());
            // Reverse vector to be opposite of velocity
            douglas::vector::scale(tmp, -1.0);
            // Calculate the new position
            double *diff = douglas::vector::project(tmp, resistanceVector);
            if(douglas::vector::magnitude(diff) > douglas::vector::magnitude(res_vel2)) {
                douglas::vector::scale(res_vel2, -1.0);
                double *n_pos = douglas::vector::add(p2->getPosition(), res_vel2);
                // Set the new position
                p2->setPosition(n_pos);
                // Delete all the old variables
                delete [] n_pos;
            } else {
                double *n_pos = douglas::vector::add(p2->getPosition(), diff);
                // Set the new position
                p2->setPosition(n_pos);
                // Delete all the old variables
                delete[] n_pos;
            }
            delete [] tmp;
            delete [] diff;
        }

        // Delete all the vectors
        delete [] vel1;
        delete [] vel2;
        delete [] wheelVector;
        delete [] resistanceVector;
        delete [] res_vel1;
        delete [] res_vel2;
    }

}