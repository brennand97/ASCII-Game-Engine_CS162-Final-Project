/**
 * Author:      Brennan Douglas
 * Date:        03/05/2017
 * Description: This is the source code for the GameObject class
 */

#include "game_object.hpp"
#include <vector>
#include <algorithm>

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
}

GameObject::GameObject(double *pos, double *hit) {
    this->pos = pos;
    this->hit = hit;
}

GameObject::GameObject(double *pos, double *vel, double *hit) {
    this->pos = pos;
    this->ppos = new double[2];
    ppos[0] = pos[0] - vel[0];
    ppos[1] = pos[1] - vel[1];
    this->hit = hit;
}

GameObject::GameObject(const GameObject &obj) : GameObject() {
    pos[0] = obj.pos[0];
    pos[1] = obj.pos[1];
    ppos[0] = obj.ppos[0];
    ppos[1] = obj.ppos[1];
}

GameObject::~GameObject() {
    delete [] pos;
    delete [] ppos;
    delete [] hit;
    for(std::vector<GameObject*>::iterator it = children.begin(); it != children.end(); it++) {
        delete (*it);
    }
}

GameObject* GameObject::getChild(int obj_id) {

    std::vector<GameObject*>::iterator it;
    for(it = children.begin(); it != children.end(); it++) {
        if((*it)->getId() == obj_id) {
            return *it;
        }
    }

    return nullptr;

}

void GameObject::step(double dt, double p_dt) {
    double *vel = new double[2];

    vel[0] = (pos[0] - ppos[0]) / p_dt;
    vel[1] = (pos[1] - ppos[1]) / p_dt;

}