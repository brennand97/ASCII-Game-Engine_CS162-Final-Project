//
// Created by Brennan on 3/16/2017.
//

#include "wall.hpp"
#include "../../personal_utilities/vec_func.hpp"
#include "../../space.hpp"

#include "../constraints/drag_constraint.hpp"

std::string Wall::TYPE = "wall";
std::string Wall::WallConstraint::TYPE = "wall_constraint";

Wall::Wall(double *top, double *bottom) : ParticleContainer() {
    this->top = douglas::vector::copy(top);
    this->bottom = douglas::vector::copy(bottom);

    wallConstraint = new WallConstraint(this);
    addSuperGlobalConstraint(wallConstraint);
}

Wall::~Wall() {
    delete [] top;
    delete [] bottom;
}

void Wall::render(Screen *screen) {
    Space* world = (Space*) getWorld();
    std::vector<Pixel> line;
    double * p_top = world->convertToPixels((const double*) top, screen);
    double * p_bot = world->convertToPixels((const double*) bottom, screen);
    screen->line(p_top, p_bot, draw_char, &line);
    delete [] p_top;
    delete [] p_bot;
    screen->addToFrame(line);
}

Wall::WallConstraint::WallConstraint(Wall *wall) : SingleConstraint() {
    addType(WallConstraint::TYPE);
    this->wall = wall;
}

void Wall::WallConstraint::fix(int iter, Particle *p) {
    double * inter_path = nullptr;
    try {
        inter_path = douglas::vector::subtract(p->getPPosition(), p->getPosition());
        douglas::vector::scale(inter_path, 1);
        double * ppos = douglas::vector::add(p->getPosition(), inter_path);
        double * intersect = douglas::vector::intersection(wall->top, wall->bottom,
                                                           p->getPosition(), ppos);

        double * wall_vec = douglas::vector::subtract(wall->top, wall->bottom);
        double * orth_wall_vec = douglas::vector::vector(-1 * wall_vec[1], wall_vec[0]);

        double * p_path = douglas::vector::subtract(p->getPosition(), p->getPPosition());
        double * o_w_p_path = douglas::vector::project(p_path, orth_wall_vec);
        double * p_w_path = douglas::vector::subtract(intersect, p->getPPosition());
        double * o_w_p_w_path = douglas::vector::project(p_w_path, orth_wall_vec);
        double * diff = douglas::vector::subtract(o_w_p_w_path, o_w_p_path);
        douglas::vector::scale(diff, 1.2);

        double * n_pos = douglas::vector::add(p->getPosition(), diff);
        p->setPosition(n_pos);

        delete [] inter_path;
        delete [] ppos;
        delete [] intersect;
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
        delete [] inter_path;
    }
}