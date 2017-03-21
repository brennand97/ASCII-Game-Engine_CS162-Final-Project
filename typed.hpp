/**
 * Author:      Brennan Douglas
 * Date:        03/06/2017
 * Description: This is the header file for the Typed class
 */

#ifndef FINAL_PROJECT_TYPED_HPP
#define FINAL_PROJECT_TYPED_HPP

#include <vector>
#include <algorithm>
#include <string>

// This class allows for all the types a derived class is to be easily determined through defined TYPE stings in
// each of the super classes.
class Typed {
protected:
    std::vector<std::string> types;
public:
    Typed(std::string type) { types.push_back(type); }
    virtual ~Typed() {};

    void addType(std::string type) { types.push_back(type); }
    std::string getType() { return types[types.size() - 1]; }
    bool isType(std::string type) { return std::find(types.begin(), types.end(), type) != types.end(); }
};

#endif //FINAL_PROJECT_TYPED_HPP
