/**
 * Author:      Brennan Douglas
 * Date:        03/05/2017
 * Description: This is the header file for the GameObject class
 */

#ifndef FINAL_PROJECT_GAME_OBJECT_HPP
#define FINAL_PROJECT_GAME_OBJECT_HPP

#include "typed.hpp"
#include "display/screen.hpp"
#include <string>
#include <vector>
#include <algorithm>

class GameObject : public Typed {
protected:
    unsigned int obj_id;
    double previous_dt = -1;
    char draw_char = '#';
    GameObject* parent = nullptr;
    GameObject* world = nullptr;
    std::vector<GameObject*> children;
    unsigned int getChildIndex(unsigned int c_obj_id);
    void stepChildren(double dt);
    void renderChildren(Screen* screen);
public:

    static unsigned int n_obj_id;
    static std::string TYPE;

    // Constructors
    GameObject();
    GameObject(const GameObject &obj);
    virtual ~GameObject();

    // Id system
    unsigned int getId() { return obj_id; }
    void setId(unsigned int id) { this->obj_id = id; }

    // GameObject Parent
    GameObject* getParent() { return parent; }
    void setParent(GameObject * parent) { this->parent = parent; world = getWorld(); }

    // GameObject Children
    std::vector<GameObject*> getChildren() { return children; }
    void addChild(GameObject* child) { child->setParent(this); children.push_back(child); }
    GameObject* getChild(unsigned int c_obj_id);
    void removeChild(GameObject * obj);
    void removeChild(unsigned int c_obj_id);

    // Recursive functions
    GameObject* getWorld();
    void getParentsOfType(std::string, std::vector<GameObject*>*);
    void getChildrenOfType(std::string, std::vector<GameObject*>*);

    // Time Step
    virtual void step(double dt);
    double getPreviousStepTime() { return previous_dt; }

    // Draw char
    char getDrawChar() { return draw_char; }
    void setDrawChar(char c) { this->draw_char = c; }

    // Virtual Render function
    virtual void render(Screen* screen) = 0;

    // Operators
    bool operator ==(const GameObject &obj) { return this->obj_id == obj.obj_id; }
    bool operator !=(const GameObject &obj) { return !((*this) == obj); }

};

#endif //FINAL_PROJECT_GAME_OBJECT_HPP
