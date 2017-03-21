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
#include "personal_utilities/douglbre_util.hpp"
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
void attachPlayerToKeys(Room***, Player*);
bool checkKey(int, Room***);

int main (int argc, char** argv) {

    // These define the size of the game worlds, in arbitrary units.
    double world_width = 100.0;
    double world_height = 50.0;

    // These define the size of the game screen, but not the total space taken up by the game
    int screen_width = 150;     // Columns in terminal
    int screen_height = 50;     // Rows of in terminal

    double time_limit = 300;  // Time limit in seconds (5 min)
    double win_delay_seconds = 2; // Time delay to win from final room enter (2 sec)

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

    std::cout << std::endl << "HOW TO:     The three keys are located in the top left corner space,";
    std::cout << std::endl << "            the middle left space, and the top right space.  Both the";
    std::cout << std::endl << "            top left and right spaces are easy, just navigate upwards";
    std::cout << std::endl << "            from the starting place, the middle and push through the";
    std::cout << std::endl << "            pinwheel to get to the left or the right.  If you keep getting";
    std::cout << std::endl << "            stuck on the pinwheel try going to the right from the middle";
    std::cout << std::endl << "            then up to get one key, then through the pinwheel from right";
    std::cout << std::endl << "            to left from up there.  To get the third and final key you";
    std::cout << std::endl << "            will need to go to the left middle and work your way down from";
    std::cout << std::endl << "            there through the tunnel to push the wall from the bottom.";
    std::cout << std::endl << "            You can then go back to the middle, go to the left room and";
    std::cout << std::endl << "            you will know be able to navigate around the moved wall. Finally";
    std::cout << std::endl << "            to end go back to the middle space." << std::endl;

    std::cout << std::endl << "TIME LIMIT: 5 minutes." << std::endl << std::endl;

    char yn;
    auto yn_valid = [](char c) -> bool {
        if(c == 'y' || c =='n') {
            return true;
        } else {
            std::cout << "You must reply 'y' for yes, or 'n' for no." << std::endl;
            return false;
        }
    };
    douglbre::user::validate_input<char>("Would you like to play the game? (y/n) ", &yn, yn_valid);
    if (yn == 'n') {
        return 0;
    }

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
    attachPlayerToKeys(grid, player);

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

    // Easy access to the middle room
    GridMM* gridMM = (GridMM*) grid[1][1];

    double dt = 0.5;
    std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point start_time = t;

    std::chrono::high_resolution_clock::time_point win_delay = t;

    while (!stop) {

        Room* room = getPlayerRoom(grid);
        if(room == nullptr) {
            std::cout << "ERROR: No room had the player in it." << std::endl;
            break;
        }

        if(!input->is_multi_threading_enabled()) {
            input->getInput();
        }

        gridMM->setMarker(1, checkKey(1, grid));
        gridMM->setMarker(2, checkKey(2, grid));
        gridMM->setMarker(3, checkKey(3, grid));

        if(room == gridMM && gridMM->getMarker(1) && gridMM->getMarker(2) && gridMM->getMarker(3)) {
            if(!win_state) {
                win_delay = std::chrono::high_resolution_clock::now();
            } else if((std::chrono::high_resolution_clock::now() - win_delay).count() / 1000000000.0 > win_delay_seconds){
                break;
            }
            win_state = true;
        }

        // Step all the rooms
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        stepRooms(grid, dt);
        screen->printValue(1, " Step Time: " +
                              std::to_string((std::chrono::high_resolution_clock::now() - t2).count() / 1000000000.0));

        // Render all the elements
        t2 = std::chrono::high_resolution_clock::now();
        room->render(screen);
        screen->printValue(2, " Render Time: " +
                std::to_string((std::chrono::high_resolution_clock::now() - t2).count() / 1000000000.0));

        // Display onto terminal
        t2 = std::chrono::high_resolution_clock::now();
        screen->displayFrame();
        screen->printValue(3, " Terminal Write Time: " +
                              std::to_string((std::chrono::high_resolution_clock::now() - t2).count() / 1000000000.0));

        // Print out stats
        screen->printValue(0, " FPS: " + std::to_string(1/dt));
        screen->printValue(5, " Room Type: " + room->getType());
        screen->printValue(7, " Time Left: " + std::to_string(time_limit - ((t - start_time).count() / 1000000000.0)));

        room->checkPlayerLocation();

        std::chrono::high_resolution_clock::time_point nt = std::chrono::high_resolution_clock::now();
        dt = (nt - t).count() / 1000000000.0;
        t = nt;

        if ((t - start_time).count() / 1000000000.0 > time_limit) {
            break;
        }
    }

    std::cout << std::endl << std::endl;
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

bool checkKey(int k_int, Room* **grid) {
    switch (k_int) {
        case 1: {
            return ((GridLM*) grid[0][1])->getKey()->getPickedUp();
        }
        case 2: {
            return ((GridLT*) grid[0][0])->getKey()->getPickedUp();
        }
        case 3: {
            return ((GridRT*) grid[2][0])->getKey()->getPickedUp();
        }
    }
    return false;
}

void attachPlayerToKeys(Room* **grid, Player* player) {
    std::vector<GameObject*>::iterator it;
    std::vector<GameObject*> particles;
    player->getChildrenOfType(Particle::TYPE, &particles);
    for(it = particles.begin(); it != particles.end(); it++) {
        Particle* p = (Particle*) *it;
        ((GridLM*) grid[0][1])->getKey()->getKeyConstraint()->addParticle(p);
        ((GridLT*) grid[0][0])->getKey()->getKeyConstraint()->addParticle(p);
        ((GridRT*) grid[2][0])->getKey()->getKeyConstraint()->addParticle(p);
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