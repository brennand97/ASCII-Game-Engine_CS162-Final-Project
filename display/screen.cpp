//
// Created by Brennan on 3/7/2017.
//

#include "screen.hpp"
#include <algorithm>

Screen::Screen(int width, int height) {
    this->width = width;
    this->height = height;
    previous_frame = nullptr;
    frame = nullptr;
    newFrame();
    newFrame();
}

Screen::~Screen() {
    delete frame;
    delete previous_frame;
}

void Screen::moveCursorVertically(int j) {
    if(j > 0) {
        std::cout << "\033[" << j << "A";
    } else if(j < 0) {
        std::cout << "\033[" << j << "B";
    }
}

void Screen::moveCursorHorizontally(int i) {
    if(i > 0) {
        std::cout << "\033[" << i << "C";
    } else if (i < 0) {
        std::cout << "\033[" << i << "D";
    }
}

void Screen::newFrame() {
    delete previous_frame;
    previous_frame = frame;
    frame = new std::vector<Pixel>();
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            Pixel p(i,j);
            frame->push_back(p);
        }
    }
}

std::vector<Pixel> Screen::pullDeltaFrame() {
    std::vector<Pixel> delta;
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            int index = i + (j * width);
            if((*frame)[index] != (*previous_frame)[index]) {
                delta.push_back((*frame)[index]);
            }
        }
    }
    return delta;
}

void Screen::addToFrame(std::vector <Pixel> add) {
    std::vector<Pixel>::iterator it;
    for(it = add.begin(); it != add.end(); it++) {
        (*std::find(frame->begin(), frame->end(), *it)).setChar((*it).getChar());
    }
}

void Screen::displayFrame() {
    std::vector<Pixel> v_frame;
//    if(first_frame) {
        first_frame = false;
        v_frame = *frame;
        for(int j = 0; j < height; j++) {
            for(int i = 0; i < width; i++) {
                int index = i + (j * width);
                std::cout << v_frame[index].getChar();
            }
            std::cout << std::endl;
        }
        moveCursorVertically(height);
//    } else {
//
//        int p_i = 0;
//        int p_j = height - 1;
//        moveCursorVertically(p_j + 1);
//        v_frame = pullDeltaFrame();
//        std::vector<Pixel>::iterator it;
//        for(it = v_frame.begin(); it != v_frame.end(); it++) {
//            //TODO this could use some optimizing
//            Pixel p = (*it);
//            int d_i = p.getI() - p_i;
//            int d_j = p.getJ() - p_j;
//            moveCursorHorizontally(d_i);
//            moveCursorVertically(d_j);
//            std::cout << p.getChar();
//            p_i = p.getI();
//            p_j = p.getJ();
//        }
//        moveCursorHorizontally( -p_i );
//        moveCursorVertically( -p_j - 1 );
//
//    }
    newFrame();
}