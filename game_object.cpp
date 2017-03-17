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
std::string GameObject::TYPE = "game_object";

GameObject::GameObject() : Typed(GameObject::TYPE) {
    obj_id = n_obj_id++;
}

GameObject::GameObject(const GameObject &obj) : Typed(GameObject::TYPE) {
    types.push_back(GameObject::TYPE);
    children = obj.children;
    obj_id = n_obj_id++;
}

GameObject::~GameObject() {
    for(std::vector<GameObject*>::iterator it = children.begin(); it != children.end(); it++) {
        delete (*it);
    }
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

void GameObject::getParentsOfType(std::string type, std::vector<GameObject*>* vec) {
    if(this->isType(type)) {
        vec->push_back(this);
    }
    if(parent != nullptr) {
        parent->getParentsOfType(type, vec);
    }
}

void GameObject::getChildrenOfType(std::string type, std::vector < GameObject * > * vec) {
    if(this->isType(type)) {
        vec->push_back(this);
    }
    if(children.size() > 0) {
        std::vector<GameObject*>::iterator it;
        for(it = children.begin(); it != children.end(); it++) {
            (*it)->getChildrenOfType(type, vec);
        }
    }
}

void GameObject::getImmediateChildrenOfType(std::string type, std::vector < GameObject * > * vec) {
    if(children.size() > 0) {
        std::vector<GameObject*>::iterator it;
        for(it = children.begin(); it != children.end(); it++) {
            if((*it)->isType(type)) {
                vec->push_back(*it);
            }
        }
    }
}

void GameObject::stepChildren(double dt) {

    std::vector<GameObject*>::iterator it;
    for(it = children.begin(); it != children.end(); it++) {
        (*it)->step(dt);
    }

}

void GameObject::renderChildren(Screen *screen) {

    std::vector<GameObject*>::iterator it;
    for(it = children.begin(); it != children.end(); it++) {
        (*it)->render(screen);
    }

}

void GameObject::step(double dt) {

    if(previous_dt < 0) {
        previous_dt = dt;
    }

    stepChildren(dt);

    previous_dt = dt;

}