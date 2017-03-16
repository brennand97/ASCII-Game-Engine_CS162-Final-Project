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

void initializeGrid(Space***, double, double);

int main (int argc, char** argv) {

    // Create double array of Space pointers
    Space* **grid = new Space**[3];
    for(int i = 0; i < 3; i++) {
        grid[i] = new Space*[3];
    }
    // Fill grid with the correct instances
    initializeGrid(grid, 100.0, 100.0);

    

    // Clear all the memory of grid including the Space pointers
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            delete grid[i][j];
        }
        delete [] grid[i];
    }
    delete [] grid;

    return 0;

}

void initializeGrid(Space*** grid, double w, double h) {
    grid[0][0] = new GridLT(w, h);
    grid[1][0] = new GridMT(w, h);
    grid[2][0] = new GridRT(w, h);
    grid[0][1] = new GridLM(w, h);
    grid[1][1] = new GridMM(w, h);
    grid[2][1] = new GridRM(w, h);
    grid[0][2] = new GridLB(w, h);
    grid[1][2] = new GridMB(w, h);
    grid[2][2] = new GridRB(w, h);
}