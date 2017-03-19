//
// Created by Brennan on 3/17/2017.
//

#include "movable_wall.hpp"
#include "../../space.hpp"
#include "../../personal_utilities/vec_func.hpp"

std::string MovableWall::TYPE = "movable_wall";
std::string MovableWall::MovableWallConstraint::TYPE = "movable_wall_constraint";

MovableWall::MovableWall(double *pos1, double *pos2, bool wall_moves) : ParticleContainer() {
    addType(MovableWall::TYPE);
    this->wall_moves = wall_moves;
    this->p1 = new Particle(douglas::vector::copy(pos1));
    this->p2 = new Particle(douglas::vector::copy(pos2));
    addChild(this->p1);
    addChild(this->p2);

    lineConstraint = new LineConstraint(douglas::vector::distance(pos1, pos2), Constraint::EQUAL);
    lineConstraint->addParticle(this->p1);
    lineConstraint->addParticle(this->p2);
    addSpecificConstraint(lineConstraint);

    movableWallConstraint = new MovableWallConstraint(this);
    addSuperGlobalConstraint(movableWallConstraint);
}

void MovableWall::render(Screen *screen) {

    Space* world = (Space*) getWorld();

    double * s_p1 = douglas::vector::copy(p1->getPosition());
    double * s_p2 = douglas::vector::copy(p2->getPosition());
    world->convertToPixels(s_p1, screen);
    world->convertToPixels(s_p2, screen);

    std::vector<Pixel> line;
    screen->line(s_p1, s_p2, draw_char, &line);
    screen->addToFrame(line);

    delete [] s_p1;
    delete [] s_p2;

}

MovableWall::MovableWallConstraint::MovableWallConstraint(MovableWall *wall) : SingleConstraint() {
    addType(MovableWall::MovableWallConstraint::TYPE);
    this->wall = wall;
}

void MovableWall::MovableWallConstraint::fix(int iter, Particle *p) {
    if(isExcluded(p))
        return;

    double * inter_path = douglas::vector::subtract(p->getPPosition(), p->getPosition());
    douglas::vector::scale(inter_path, 1);
    double * ppos = douglas::vector::add(p->getPosition(), inter_path);

    double * intersect = nullptr;
    try {
        intersect = douglas::vector::intersection(wall->p1->getPosition(), wall->p2->getPosition(),
                                                  p->getPosition(), ppos);

        double * wall_vec = douglas::vector::subtract(wall->p1->getPosition(), wall->p2->getPosition());
        double * orth_wall_vec = douglas::vector::vector(-1 * wall_vec[1], wall_vec[0]);

        double * p_path = douglas::vector::subtract(p->getPosition(), p->getPPosition());
        double * o_w_p_path = douglas::vector::project(p_path, orth_wall_vec);
        double * p_w_path = douglas::vector::subtract(intersect, p->getPPosition());
        double * o_w_p_w_path = douglas::vector::project(p_w_path, orth_wall_vec);
        double * diff = douglas::vector::subtract(o_w_p_w_path, o_w_p_path);
        douglas::vector::scale(diff, 1.2);

        double * p_diff = douglas::vector::copy(diff);
        if(wall->wall_moves) {
            douglas::vector::scale(p_diff, 0.5);
        }
        double * n_pos = douglas::vector::add(p->getPosition(), diff);
        p->setPosition(n_pos);

        if(wall->wall_moves) {
            douglas::vector::scale(diff, -0.5);
            double wall_length = douglas::vector::magnitude(wall_vec);
            double r1 = douglas::vector::distance(wall->p2->getPosition(), intersect) / wall_length;
            double r2 = douglas::vector::distance(wall->p1->getPosition(), intersect) / wall_length;
            double lambda = 1 / ((r1 * r1) + (r2 * r2));

            double *p1_diff = douglas::vector::copy(diff);
            douglas::vector::scale(p1_diff, r1 * lambda);
            double *p1_n_pos = douglas::vector::add(p1_diff, wall->p1->getPosition());
            wall->p1->setPosition(p1_n_pos);

            double *p2_diff = douglas::vector::copy(diff);
            douglas::vector::scale(p2_diff, r2 * lambda);
            double *p2_n_pos = douglas::vector::add(p2_diff, wall->p2->getPosition());
            wall->p2->setPosition(p2_n_pos);

            delete [] p1_n_pos;
            delete [] p2_n_pos;
            delete [] p1_diff;
            delete [] p2_diff;
        }

        delete [] p_diff;
        delete [] wall_vec;
        delete [] orth_wall_vec;
        delete [] p_path;
        delete [] o_w_p_path;
        delete [] p_w_path;
        delete [] o_w_p_w_path;
        delete [] diff;
        delete [] n_pos;
    } catch (std::out_of_range e) {
        // There is no intersection of the lines
    }

    delete [] inter_path;
    delete [] ppos;
    delete [] intersect;
}