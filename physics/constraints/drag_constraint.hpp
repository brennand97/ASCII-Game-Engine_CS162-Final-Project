/**
 * Author:      Brennan Douglas
 * Date:        03/06/2017
 * Description: This is the header file for the DragConstraint class
 */

#ifndef FINAL_PROJECT_DRAG_CONSTRAINT_HPP
#define FINAL_PROJECT_DRAG_CONSTRAINT_HPP

#include "single_constraint.hpp"
#include <string>

// This class slows a particle down proportionally to its speed.
class DragConstraint : public SingleConstraint {
private:
    double drag;

public:

    static std::string TYPE;

    DragConstraint(double);

    double getDrag() { return drag; }
    void setDrag(double drag) { this->drag = drag; }

    void fix(int, Particle*);
};

#endif //FINAL_PROJECT_DRAG_CONSTRAINT_HPP
