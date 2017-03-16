//
// Created by Brennan on 3/16/2017.
//

#ifndef FINAL_PROJECT_ROOM_HPP
#define FINAL_PROJECT_ROOM_HPP

#include "../../space.hpp"

class Room : public Space {
public:

    static std::string TYPE;

    Room(double u_w, double u_h);

};

#endif //FINAL_PROJECT_ROOM_HPP
