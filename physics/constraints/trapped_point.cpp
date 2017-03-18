//
// Created by Brennan on 3/18/2017.
//

#include "trapped_point.hpp"
#include "../../personal_utilities/vec_func.hpp"
#include "fixed_point.hpp"
#include "../particle_container.hpp"

std::string TrappedPoint::TYPE = "trapped_point";

TrappedPoint::TrappedPoint(double radius, double *point) : SingleConstraint() {
    addType(TrappedPoint::TYPE);
    this->radius = radius;
    this->point = douglas::vector::copy(point);
}

TrappedPoint::~TrappedPoint() {
    delete [] this->point;
}

int TrappedPoint::togglesGetParticleId(Particle *particle) {
    for(unsigned int i = 0; i < toggles.size(); i++) {
        if(toggles[i].id == particle->getId()) {
            return i;
        }
    }
    return -1;
}

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
                //std::cout << "trapped";
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