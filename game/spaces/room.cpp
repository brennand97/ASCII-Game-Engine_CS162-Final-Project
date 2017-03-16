//
// Created by Brennan on 3/16/2017.
//

#include "room.hpp"

std::string Room::TYPE = "room";

Room::Room(double u_w, double u_h) : Space(u_w, u_h) {
    addType(Room::TYPE);
}