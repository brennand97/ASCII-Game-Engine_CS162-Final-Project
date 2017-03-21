/**
 * Author:      Brennan Douglas
 * Date:        03/07/2017
 * Description: This file holds the header for the screen class
 */

#ifndef FINAL_PROJECT_SCREEN_HPP
#define FINAL_PROJECT_SCREEN_HPP

#include <iostream>
#include <vector>
#include <string>
#include "pixel.hpp"

// Screen abstracts the pixel and frame calculations as well as the printing to the screen.
// It handles it correctly with and arbitrary integer width and height.
class Screen {
protected:

    // To hold the necessary values for a robust line printing system on the right edge of the screen
    struct sideline {
        std::string s;
        int n;
        int c_l;
    };

    int width, height;
    bool first_frame = true;

    std::vector<Pixel>* previous_frame;
    std::vector<Pixel>* frame;

    std::vector<sideline> sideLines;

    void newFrame();
    std::vector<Pixel> pullFrame();
    std::vector<Pixel> pullDeltaFrame();

    void moveCursorVertically(int j);
    void moveCursorHorizontally(int i);

    // Fast absolute value for line algorithm
    double fabs(double d) {
        if ( d < 0 ) {
            return -d;
        } else {
            return d;
        }
    }

    // Fast absolute value for line algorithm
    int fabs(int d) {
        if ( d < 0 ) {
            return -d;
        } else {
            return d;
        }
    }

public:

    Screen(int width, int height);
    ~Screen();

    int getWidth() { return width; }
    int getHeight() { return height; }

    void addToFrame(std::vector<Pixel>);
    void displayFrame();

    void printValue(int j, std::string value);
    void printLines();
    void clearLines();

    void line(double * p1, double * p2, char c, std::vector<Pixel>* vec);
    void line(const double * p1, const double * p2, char c, std::vector<Pixel>* vec);
    void line(double x1, double y1, double x2, double y2, char c, std::vector<Pixel>* vec);
    void bresenhamLine(double * p1, double * p2, char c, std::vector<Pixel>* vec);
    void bresenhamLine(double x1, double y1, double x2, double y2, char c, std::vector<Pixel>* vec);
    void outlineTriangle(double * p1, double * p2, double * p3, char c, std::vector<Pixel>* vec);

};

#endif //FINAL_PROJECT_SCREEN_HPP
