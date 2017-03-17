/**
 * Author:      Brennan Douglas
 * Date:        03/05/2017
 * Description: This file is the entry point for the game
 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "personal_utilities/vec_func.hpp"
#include "display/screen.hpp"
#include "game_object.hpp"
#include "physics/objects/box.hpp"
#include "game/player/wheel.hpp"
#include "game/player/player.hpp"
#include "input.hpp"

#include "game/spaces/room.hpp"
#include "game/spaces/grid_tiles.hpp"

void initializeGrid(Room***, double, double);
void initializeInput(Input*, Player*);
void move(Player* player, Space* from, Space* to);
void createPlayer(Player*);

int main (int argc, char** argv) {

    // create double array of space pointers
    Room* **grid = new Room**[3];
    for(int i = 0; i < 3; i++) {
        grid[i] = new Room*[3];
    }
    // fill grid with the correct instances
    initializeGrid(grid, 100.0, 100.0);

    // Create the player
    Player* player;
    createPlayer(player);

    // Boolean to tell the loop to stop
    bool stop = false;

    // Input system initialized
    Input* input = new Input();
    input->listenTo('q', [&input, &stop](double dt) -> void {
        stop = true;
        input->stop();
    });
    initializeInput(input, player);
    //input->listen();

    double * l1_p1 = douglas::vector::vector(1,0);
    double * l1_p2 = douglas::vector::vector(1,2);
    double * l2_p1 = douglas::vector::vector(2,0);
    double * l2_p2 = douglas::vector::vector(0,2);
    try {
        double * intersect = douglas::vector::intersection(l1_p1, l1_p2, l2_p1, l2_p2);
        std::cout << "(" << intersect[0] << ", " << intersect[1] << ")" << std::endl;
        delete [] intersect;
    } catch ( std::out_of_range e ) {
        std::cout << e.what() << std::endl;
    }
    delete [] l1_p1;
    delete [] l1_p2;
    delete [] l2_p1;
    delete [] l2_p2;

    //input->end();
    delete input;
    // clear all the memory of grid including the space pointers
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            delete grid[i][j];
        }
        delete [] grid[i];
    }
    delete [] grid;

    return 0;

}

void initializeGrid(Room* **grid, double w, double h) {
    grid[0][0] = new GridLT(w, h);
    grid[1][0] = new GridMT(w, h);
    grid[2][0] = new GridRT(w, h);
    grid[0][1] = new GridLM(w, h);
    grid[1][1] = new GridMM(w, h);
    grid[2][1] = new GridRM(w, h);
    grid[0][2] = new GridLB(w, h);
    grid[1][2] = new GridMB(w, h);
    grid[2][2] = new GridRB(w, h);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (i > 0) {
                grid[i][j]->setSpace(3, grid[i - 1][j]);
            }
            if (i < 2) {
                grid[i][j]->setSpace(1, grid[i + 1][j]);
            }
            if (j > 0) {
                grid[i][j]->setSpace(0, grid[i][j - 1]);
            }
            if (j < 2) {
                grid[i][j]->setSpace(2, grid[i][j + 1]);
            }
        }
    }
}

void createPlayer(Player* player) {
    double * player_pos = douglas::vector::vector(2.5, 5.0);
    player = new Player(player_pos, 5.0, 10.0, 3.0, 1000.0, 1000.0);
    delete [] player_pos;
}

void initializeInput(Input* input, Player* player) {

    double accel = 10;
    double angle = douglas::pi / 7.0;

    input->listenTo('w', [&accel, &player](double dt) -> void {
        double vel = accel;
        if (dt < 0.1) {
            vel *= dt * dt;
        } else {
            vel *= 0.01;
        }
        std::vector<GameObject*> gos;
        player->getChildrenOfType(Wheel::TYPE, &gos);
        std::vector<GameObject*>::iterator it = gos.end();
        it--;
        Wheel* b_w = (Wheel*) (*it);
        double * b_vel = b_w->getWheelVector();
        douglas::vector::unitVector(b_vel);
        douglas::vector::scale(b_vel, vel);
        b_w->addVelocity(b_vel);
        delete [] b_vel;

    });
    input->listenTo('s', [&accel, &player](double dt) -> void {
        double vel = -1 * accel;
        if (dt < 0.1) {
            vel *= dt * dt;
        } else {
            vel *= 0.01;
        }
        std::vector<GameObject*> gos;
        player->getChildrenOfType(Wheel::TYPE, &gos);
        std::vector<GameObject*>::iterator it = gos.end();
        it--;
        Wheel* b_w = (Wheel*) (*it);
        double * b_vel = b_w->getWheelVector();
        douglas::vector::unitVector(b_vel);
        douglas::vector::scale(b_vel, vel);
        b_w->addVelocity(b_vel);
        delete [] b_vel;
    });
    input->listenTo('d', [&accel, &angle, &player](double dt) -> void {
        std::vector<GameObject*> gos;
        player->getChildrenOfType(Wheel::TYPE, &gos);
        std::vector<GameObject*>::iterator it = gos.begin();
        ((Wheel*) (*it))->setAngle(angle);
    });
    input->listenTo('a', [&accel, &angle, &player](double dt) -> void {
        std::vector<GameObject*> gos;
        player->getChildrenOfType(Wheel::TYPE, &gos);
        std::vector<GameObject*>::iterator it = gos.begin();
        ((Wheel*) (*it))->setAngle(-1 * angle);
    });

}