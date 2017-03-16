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

#include "space.hpp"
#include "game/spaces/grid.hpp"

void initializeGrid(Space*[3][3]);

int main (int argc, char** argv) {

    Space* grid[3][3];
    grid[0][0] = new GridLT(100.0, 100.0);

    return 0;

}

void initializeGrid(Space*** grid) {

}