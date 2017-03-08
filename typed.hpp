//
// Created by Brennan on 3/7/2017.
//

#ifndef FINAL_PROJECT_TYPED_HPP
#define FINAL_PROJECT_TYPED_HPP

#include <vector>
#include <algorithm>
#include <string>

class Typed {
protected:
    std::vector<std::string> types;
public:
    Typed(std::string type) { types.push_back(type); }
    ~Typed() {};

    void addType(std::string type) { types.push_back(type); }
    std::string getType() { return types[types.size() - 1]; }
    bool isType(std::string type) { return std::find(types.begin(), types.end(), type) != types.end(); }
};

#endif //FINAL_PROJECT_TYPED_HPP
