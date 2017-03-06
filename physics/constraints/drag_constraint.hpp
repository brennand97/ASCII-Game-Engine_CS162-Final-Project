//
// Created by Brennan on 3/6/2017.
//

#ifndef FINAL_PROJECT_DRAG_CONSTRAINT_HPP
#define FINAL_PROJECT_DRAG_CONSTRAINT_HPP

#include "constraint.hpp"

class DragConstraint : public Constraint {
private:
    double drag;
    void applyDrag(Particle&);
public:
    DragConstraint(double);
    double getDrag() { return drag; }
    void setDrag(double drag) { this->drag = drag; }
    void fix(Particle*, Particle*);
};

#endif //FINAL_PROJECT_DRAG_CONSTRAINT_HPP
