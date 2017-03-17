//
// Created by Brennan on 3/16/2017.
//

#ifndef FINAL_PROJECT_ROOM_HPP
#define FINAL_PROJECT_ROOM_HPP

#include "../../space.hpp"
#include "../player/player.hpp"

class Room : public Space {
protected:

    Player* player = nullptr;

public:

    static std::string TYPE;

    Room(double u_w, double u_h);

    void setPlayer(Player*);
    void removePlayer();
    void checkPlayerLocation();
    bool hasPlayer() { return player != nullptr; }

    void step(double dt);

};

#endif //FINAL_PROJECT_ROOM_HPP
