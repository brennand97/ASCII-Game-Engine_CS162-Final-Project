//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_DRAG_CONSTRAINT_HPP
#define FINAL_PROJECT_DRAG_CONSTRAINT_HPP

#include "single_constraint.hpp"
#include <string>

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
