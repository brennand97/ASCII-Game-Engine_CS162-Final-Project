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
Room* getPlayerRoom(Room***);
void stepRooms(Room***, double);
void printEnding(bool state);

int main (int argc, char** argv) {

    // These define the size of the game worlds, in arbitrary units.
    double world_width = 100.0;
    double world_height = 50.0;

    // These define the size of the game screen, but not the total space taken up by the game
    int screen_width = 150;     // Columns in terminal
    int screen_height = 50;     // Rows of in terminal

    double time_limit = 300;  // Time limit in seconds (5 min)

    bool win_state = false;   // True means successful

    std::cout << std::endl << "WARNING:    If your terminal is not around 200x60 (col x row) the graphics will glitch out." << std::endl;
    std::cout << std::endl << "NOTE:       Best played in full screen on a local machine, though ssh does work, it will just lag sometimes." << std::endl;
    std::cout << std::endl << "INFO:       In this game you will play as a car and you need to collect";
    std::cout << std::endl << "            3 keys from nine different rooms arranged in a grid.  Use WASD";
    std::cout << std::endl << "            for the movement, and due to how keyboard input is accepted";
    std::cout << std::endl << "            from the keyboard only one key can be pressed at a time and";
    std::cout << std::endl << "            there is approximately a 300 millisecond pause between holding";
    std::cout << std::endl << "            the key and it sending a constant stream of input, so tapping";
    std::cout << std::endl << "            is the best way to move. Press 'q' to quit." << std::endl;

    std::cout << std::endl << "TIME LIMIT: 5 minutes." << std::endl;

    std::cout << std::endl << "Press 'q' to quit." << std::endl;

    // create double array of space pointers
    Room* **grid = new Room**[3];
    for(int i = 0; i < 3; i++) {
        grid[i] = new Room*[3];
    }
    // fill grid with the correct instances
    initializeGrid(grid, world_width, world_height);

    // Create the player
    double * player_pos = douglas::vector::vector(20, 20);
    Player* player = new Player(player_pos, 5.0, 10.0, 3.0, 100000.0, 100000.0);
    delete [] player_pos;
    grid[1][1]->setPlayer(player);

    // Boolean to tell the loop to stop
    bool stop = false;

    // Input system initialized
    Input* input = new Input();
    double accel = 20;
    double angle = douglas::pi / 9.0;
    input->listenTo('r', [&player](double dt) -> void {
        player->setChanged(!player->getChanged());
        player->getChildren()[0]->setChanged(!player->getChildren()[0]->getChanged());
        player->getChildren()[1]->setChanged(!player->getChildren()[1]->getChanged());
    });
    input->listenTo('q', [&input, &stop](double dt) -> void {
        stop = true;
        input->stop();
    });
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
    input->listen();

    // Create screen
    Screen* screen = new Screen(screen_width, screen_height);

    double dt = 0.5;
    std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point start_time = t;

    while (!stop) {

        Room* room = getPlayerRoom(grid);
        if(room == nullptr) {
            std::cout << "ERROR: No room had the player in it." << std::endl;
            break;
        }

        if(!input->is_multi_threading_enabled()) {
            input->getInput();
        }

        stepRooms(grid, dt);

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        room->render(screen);
        screen->printValue(1, " Render time: " +
                std::to_string((std::chrono::high_resolution_clock::now() - t2).count() / 1000000000.0));
        screen->displayFrame();
        screen->printValue(0, " FPS: " + std::to_string(1/dt));
        screen->printValue(2, " Room Type: " + room->getType());
        screen->printValue(5, " Time Left: " + std::to_string(time_limit - ((t - start_time).count() / 1000000000.0)));

        room->checkPlayerLocation();

        std::chrono::high_resolution_clock::time_point nt = std::chrono::high_resolution_clock::now();
        dt = (nt - t).count() / 1000000000.0;
        t = nt;

        if ((t - start_time).count() / 1000000000.0 > time_limit) {
            break;
        }
    }

    printEnding(win_state);

    delete input;
    // clear all the memory of grid including the space pointers
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            delete grid[i][j];
        }
        delete [] grid[i];
    }
    delete [] grid;
    delete screen;

    return 0;

}

void printEnding(bool state) {
    if(state) {

    } else {
        std::cout << ".\n.\n.\n.\n." << std::endl;
        std::cout << "Game Over." << std::endl;
    }
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

Room* getPlayerRoom(Room* **grid) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (grid[i][j]->hasPlayer()) {
                return grid[i][j];
            }
        }
    }
    return nullptr;
}

void stepRooms(Room* **grid, double dt) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            grid[i][j]->step(dt);
        }
    }
}