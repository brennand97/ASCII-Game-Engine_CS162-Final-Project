//
// Created by Brennan on 3/16/2017.
//

#include "room.hpp"

std::string Room::TYPE = "room";

Room::Room(double u_w, double u_h) : Space(u_w, u_h) {
    addType(Room::TYPE);
}

void Room::setPlayer(Player * p) {
    this->player = p;
    addChild(p);
}

void Room::removePlayer() {
    if (player != nullptr) {
        removeChild(this->player);
        player = nullptr;
    }
}

void Room::checkPlayerLocation() {
    if (player != nullptr) {
        double * p_mid = player->getPlayerMidPoint();

        if(p_mid[1] >= 0 && p_mid[1] < unit_height) {
            // Signifies either right or left side
            if(p_mid[0] < 0) {
                // Signifies left side
                if(neighbors[3] != nullptr) {
                    player->movePlayerBy(neighbors[3]->getWidth() - 1, 0);
                    ((Room*) neighbors[3])->setPlayer(player);
                    removePlayer();
                }
            } else if (p_mid[0] >= unit_width) {
                // Signifies right side
                if(neighbors[1] != nullptr) {
                    player->movePlayerBy( -1 * (unit_width - 1), 0);
                    ((Room*) neighbors[1])->setPlayer(player);
                    removePlayer();
                }
            }
        } else if (p_mid[0] >= 0 && p_mid[0] < unit_width) {
            // Signifies either top or bottom side
            if(p_mid[1] < 0) {
                // Signifies bottom side
                if(neighbors[2] != nullptr) {
                    player->movePlayerBy(0, neighbors[2]->getHeight() - 1);
                    ((Room*) neighbors[2])->setPlayer(player);
                    removePlayer();
                }
            } else if (p_mid[1] >= unit_height) {
                // Signifies top side
                if(neighbors[0] != nullptr) {
                    player->movePlayerBy(0, -1 * (unit_height - 1));
                    ((Room*) neighbors[0])->setPlayer(player);
                    removePlayer();
                }
            }
        }

        delete [] p_mid;
    }
}