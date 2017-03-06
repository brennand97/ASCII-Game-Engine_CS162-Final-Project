/**
 * Author:      Brennan Douglas
 * Date:        03/05/2017
 * Description: This is the header file for the GameObject class
 */

#ifndef FINAL_PROJECT_GAME_OBJECT_HPP
#define FINAL_PROJECT_GAME_OBJECT_HPP

#include <vector>

class GameObject {
private:
    static unsigned int n_obj_id;
    unsigned int obj_id;
    double *ppos;
    double *pos;
    double *hit;
    double mass;
    GameObject* parent;
    std::vector<GameObject*> children;
public:
    GameObject();
    GameObject(double * pos, double * hit);
    GameObject(double * pos, double * vel, double * hit);
    GameObject(const GameObject &obj);
    virtual ~GameObject();
    int getId() { return obj_id; }
    double getMass() { return mass; }
    void setMass(double mass) { this->mass = mass; }
    const double * getHitBox() { return hit; }
    void setHitBox(double * hit) { this->hit = hit; }
    const double * getPosition() { return pos; }
    void setPosition(double * pos) { this->pos = pos; }
    const double * getPPosition() { return ppos; }
    void setPPosition(double * ppos) { this->ppos = ppos; }
    GameObject* getParent() { return parent; }
    void setParent(GameObject * parent) { this->parent = parent; }
    std::vector<GameObject*> getChildren() { return children; }
    GameObject* getChild(int obj_id);
    void removeChild(GameObject * obj);
    void removeChild(int obj_id);
    virtual void step(double dt, double p_dt);
    bool operator ==(const GameObject &obj) { return this->obj_id == obj.obj_id; }
    bool operator !=(const GameObject &obj) { return !((*this) == obj); }
};

#endif //FINAL_PROJECT_GAME_OBJECT_HPP
