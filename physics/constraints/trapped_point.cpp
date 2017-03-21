/**
 * Author:      Brennan Douglas
 * Date:        03/18/2017
 * Description: This is the source file for the TrappedPoint class
 */

#include "trapped_point.hpp"
#include "../../personal_utilities/vec_func.hpp"
#include "fixed_point.hpp"
#include "../particle_container.hpp"

std::string TrappedPoint::TYPE = "trapped_point";

// Constructor for TrappedPoint
// <radius> minimum distance a particle has to be to become fixed
// <point> point at which the particle will become fixed to
TrappedPoint::TrappedPoint(double radius, double *point) : SingleConstraint() {
    addType(TrappedPoint::TYPE);
    this->radius = radius;
    this->point = douglas::vector::copy(point);
}

// TrappedPoint deconstructor
TrappedPoint::~TrappedPoint() {
    delete [] this->point;
}

// Get particle index in toggles vector
int TrappedPoint::togglesGetParticleId(Particle *particle) {
    for(unsigned int i = 0; i < toggles.size(); i++) {
        if(toggles[i].id == particle->getId()) {
            return i;
        }
    }
    return -1;
}

// Checks distance between point and particle then applies fixed point if possible
void TrappedPoint::fix(int iter, Particle *p) {
    double dist = douglas::vector::distance(p->getPosition(), this->point);
    if (dist < radius) {
        int index = -1;
        if((index = togglesGetParticleId(p)) > -1) {
            if(!toggles[index].trapped) {
                FixedPoint* fp = new FixedPoint(this->point);
                fp->addParticle(p);
                ParticleContainer* parent = (ParticleContainer*) p->getParent();
                parent->addSpecificConstraint(fp);
            }
        } else {
            particle_toggle pt;
            pt.id = p->getId();
            pt.trapped = true;
            toggles.push_back(pt);

            FixedPoint* fp = new FixedPoint(this->point);
            fp->addParticle(p);
            ParticleContainer* parent = (ParticleContainer*) p->getParent();
            parent->addSpecificConstraint(fp);
        }
    } else {
        int index = -1;
        if((index = togglesGetParticleId(p)) == -1) {
            particle_toggle pt;
            pt.id = p->getId();
            pt.trapped = false;
            toggles.push_back(pt);
        }
    }
}