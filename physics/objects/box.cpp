/**
 * Author:      Brennan Douglas
 * Date:        03/06/2017
 * Description: This is the source file for the Box class
 */

#include "box.hpp"
#include "../particle.hpp"
#include "../../space.hpp"
#include <string>
#include <cmath>
#include <algorithm>

std::string Box::TYPE = "box";

// Box constructor
// <pos> bottom left point at which the box will be initiated
// <width> width of the box
// <height> height of the box
Box::Box(double *pos, double width, double height) : ConvexPolygon(true, 1) {
    addType(Box::TYPE);

    this->width = width;
    this->height = height;

    double dx, dy;
    if(pos == nullptr) {
        dx = 0;
        dy = 0;
    } else {
        dx = pos[0];
        dy = pos[1];
    }

    double * pos1 = new double[2];
    pos1[0] = dx;
    pos1[1] = dy;
    double * pos2 = new double[2];
    pos2[0] = width + dx;
    pos2[1] = dy;
    double * pos3 = new double[2];
    pos3[0] = width + dx;
    pos3[1] = dy + height;
    double * pos4 = new double[2];
    pos4[0] = dx;
    pos4[1] = dy + height;

    Particle* p1 = new Particle(pos1);
    Particle* p2 = new Particle(pos2);
    Particle* p3 = new Particle(pos3);
    Particle* p4 = new Particle(pos4);

    addChild(p1);
    addChild(p2);
    addChild(p3);
    addChild(p4);

    vertices.push_back(p1);
    vertices.push_back(p2);
    vertices.push_back(p3);
    vertices.push_back(p4);

    num_vertices = vertices.size();

    setConstraints();

    mmc_bottom = new MovableWall::MovableWallConstraint(p1, p2);
    mmc_right = new MovableWall::MovableWallConstraint(p2, p3);
    mmc_top = new MovableWall::MovableWallConstraint(p3, p4);
    mmc_left = new MovableWall::MovableWallConstraint(p4, p1);

    addSuperGlobalConstraint(mmc_bottom);
    addSuperGlobalConstraint(mmc_right);
    addSuperGlobalConstraint(mmc_top);
    addSuperGlobalConstraint(mmc_left);
}

// Default Box deconstructor
Box::~Box() {}