/**
 * Author:      Brennan Douglas
 * Date:        03/05/2017
 * Description: This is the source code for the GameObject class
 */

#include "game_object.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

unsigned int GameObject::n_obj_id = 0;

GameObject::GameObject() {
    pos = new double[2];
    pos[0] = 0;
    pos[1] = 0;
    ppos = new double[2];
    ppos[0] = 0;
    ppos[1] = 0;
    hit = new double[2];
    hit[0] = 0;
    hit[1] = 0;
    obj_id = n_obj_id++;
}

GameObject::GameObject(double *pos, double *hit) {
    if(pos != nullptr) {
        this->pos = pos;
    } else {
        pos = new double[2];
        pos[0] = 0;
        pos[1] = 0;
    }
    if(hit != nullptr) {
        this->hit = hit;
    } else {
        hit = new double[2];
        hit[0] = 0;
        hit[1] = 0;
    }
    obj_id = n_obj_id++;
}

GameObject::GameObject(double *pos, double *vel, double *hit) {
    if(pos != nullptr) {
        this->pos = pos;
    } else {
        pos = new double[2];
        pos[0] = 0;
        pos[1] = 0;
    }
    this->ppos = new double[2];
    if(vel != nullptr) {
        ppos[0] = pos[0] - vel[0];
        ppos[1] = pos[1] - vel[1];
    } else {
        ppos[0] = pos[0];
        ppos[1] = pos[1];
    }
    if(hit != nullptr) {
        this->hit = hit;
    } else {
        hit = new double[2];
        hit[0] = 0;
        hit[1] = 0;
    }
    obj_id = n_obj_id++;
}

GameObject::GameObject(const GameObject &obj) : GameObject() {
    pos[0] = obj.pos[0];
    pos[1] = obj.pos[1];
    ppos[0] = obj.ppos[0];
    ppos[1] = obj.ppos[1];
    obj_id = n_obj_id++;
}

GameObject::~GameObject() {
    delete [] pos;
    delete [] ppos;
    delete [] hit;
    for(std::vector<GameObject*>::iterator it = children.begin(); it != children.end(); it++) {
        delete (*it);
    }
}

const double* GameObject::getAbsPosition() {
    double * abs = new double[2];
    const double * ap_pos = parent->getAbsPosition();
    abs[0] = ap_pos[0] + pos[0];
    abs[1] = ap_pos[1] + pos[1];
    return abs;
}

const double* GameObject::getAbsPPosition() {
    double * pabs = new double[2];
    const double * ap_ppos = parent->getAbsPPosition();
    pabs[0] = ap_ppos[0] + ppos[0];
    pabs[1] = ap_ppos[1] + ppos[1];
    return pabs;
}

unsigned int GameObject::getChildIndex(unsigned int c_obj_id) {

    std::vector<GameObject*>::iterator it;
    for(unsigned int i = 0; i < children.size(); i++) {
        if (children[i]->getId() == c_obj_id) {
            return i;
        }
    }

    throw std::invalid_argument("Child was not found");

}

GameObject* GameObject::getChild(unsigned int c_obj_id) {

    try {
        return getChild(c_obj_id);
    } catch ( std::exception e ) {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }

}

void GameObject::removeChild(GameObject *obj) {

    removeChild(obj->getId());

}

void GameObject::removeChild(unsigned int c_obj_id) {

    try {
        int index = getChildIndex(c_obj_id);
        children.erase(children.begin() + index, children.begin() + index + 1);
    } catch ( std::exception e ) {
        std::cerr << e.what() << std::endl;
    }

}

GameObject* GameObject::getWorld() {
    if(parent != nullptr) {
        return parent->getWorld();
    } else {
        return this;
    }
}

void GameObject::stepChildren(double dt) {

    std::vector<GameObject*>::iterator it;
    for(it = children.begin(); it != children.end(); it++) {
        (*it)->step(dt);
    }

}

void GameObject::step(double dt) {

    if(previous_dt < 0) {
        previous_dt = dt;
    }

    double *n_pos = new double[2];
    double *vel = new double[2];

    vel[0] = (pos[0] - ppos[0]) / previous_dt;
    vel[1] = (pos[1] - ppos[1]) / previous_dt;

    n_pos[0] = pos[0] + (vel[0] * dt);
    n_pos[1] = pos[1] + (vel[1] * dt);

    delete [] ppos;
    ppos = pos;
    pos = n_pos;

    delete [] vel;

    stepChildren(dt);

    previous_dt = dt;

}