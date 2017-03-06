/**
 * Author:      Brennan Douglas
 * Date:        03/05/2017
 * Description: This is the header file for the GameObject class
 */

#ifndef FINAL_PROJECT_GAME_OBJECT_HPP
#define FINAL_PROJECT_GAME_OBJECT_HPP

#include <vector>

class GameObject {
protected:
    unsigned int obj_id;
    double *ppos;
    double *pos;
    double *hit;
    double mass;
    GameObject* parent = nullptr;
    GameObject* world = nullptr;
    std::vector<GameObject*> children;
    unsigned int getChildIndex(unsigned int c_obj_id);
public:

    // Constructors
    GameObject();
    GameObject(double * pos, double * hit);
    GameObject(double * pos, double * vel, double * hit);
    GameObject(const GameObject &obj);
    virtual ~GameObject();

    // Id system
    static unsigned int n_obj_id;
    unsigned int getId() { return obj_id; }
    void setId(unsigned int id) { this->obj_id = id; }

    // Physics Data
    double getMass() { return mass; }
    void setMass(double mass) { this->mass = mass; }
    const double * getHitBox() { return hit; }
    void setHitBox(double * hit) { this->hit = hit; }

    // Position Data
    const double * getPosition() { return pos; }
    const double * getAbsPosition();
    void setPosition(double * pos) { this->pos = pos; }
    const double * getPPosition() { return ppos; }
    const double * getAbsPPosition();
    void setPPosition(double * ppos) { this->ppos = ppos; }

    // GameObject Parent
    GameObject* getParent() { return parent; }
    void setParent(GameObject * parent) { this->parent = parent; world = getWorld(); }

    // GameObject Children
    std::vector<GameObject*> getChildren() { return children; }
    void addChild(GameObject* child) { children.push_back(child); }
    GameObject* getChild(unsigned int c_obj_id);
    void removeChild(GameObject * obj);
    void removeChild(unsigned int c_obj_id);

    // Recursive function to get base GameObject
    GameObject* getWorld();

    // Time Step
    virtual void step(double dt, double p_dt);

    // Operators
    bool operator ==(const GameObject &obj) { return this->obj_id == obj.obj_id; }
    bool operator !=(const GameObject &obj) { return !((*this) == obj); }
    double &operator [](int i) { return pos[i]; }
};



#endif //FINAL_PROJECT_GAME_OBJECT_HPP
