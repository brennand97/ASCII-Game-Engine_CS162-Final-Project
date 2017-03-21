/**
 * Author:      Brennan Douglas
 * Date:        03/06/2017
 * Description: This is the header file for the Box class
 */

#ifndef FINAL_PROJECT_BOX_HPP
#define FINAL_PROJECT_BOX_HPP

#include "../objects/convex_polygon.hpp"
#include "../constraints/line_constraint.hpp"
#include "../objects/movable_wall.hpp"
#include <string>

// Makes a rectangle that can be pushed around.
class Box : public ConvexPolygon {
private:
    double width;
    double height;
    MovableWall::MovableWallConstraint* mmc_left;
    MovableWall::MovableWallConstraint* mmc_top;
    MovableWall::MovableWallConstraint* mmc_right;
    MovableWall::MovableWallConstraint* mmc_bottom;
public:

    static std::string TYPE;

    Box(double * pos, double width, double height);
    ~Box();

    double getWidth() { return width; }
    double getHeight() { return height; }

};

#endif //FINAL_PROJECT_BOX_HPP
