//
// Created by Brennan on 3/7/2017.
//

#ifndef FINAL_PROJECT_SCREEN_HPP
#define FINAL_PROJECT_SCREEN_HPP

#include <iostream>
#include <vector>
#include "pixel.hpp"

class Screen {
protected:

    int width, height;
    bool first_frame = true;

    std::vector<Pixel>* previous_frame;
    std::vector<Pixel>* frame;

    void newFrame();
    std::vector<Pixel> pullFrame();
    std::vector<Pixel> pullDeltaFrame();

    void moveCursorVertically(int j);
    void moveCursorHorizontally(int i);

public:

    Screen(int width, int height);
    ~Screen();

    void addToFrame(std::vector<Pixel>);
    void displayFrame();

};

#endif //FINAL_PROJECT_SCREEN_HPP
