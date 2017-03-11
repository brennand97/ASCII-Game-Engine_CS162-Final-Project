//
// Created by Brennan on 3/7/2017.
//

#ifndef FINAL_PROJECT_SCREEN_HPP
#define FINAL_PROJECT_SCREEN_HPP

#include <iostream>
#include <vector>
#include <string>
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

    int signum(int a, bool zero = true) {
        if (a > 0) {
            return 1;
        } else if (a < 0) {
            return -1;
        } else if (zero) {
            return 0;
        } else {
            return 1;
        }
    };

    double fabs(double d) {
        if ( d < 0 ) {
            return -d;
        } else {
            return d;
        }
    }

    int fabs(int d) {
        if ( d < 0 ) {
            return -d;
        } else {
            return d;
        }
    }

    void bresenhamNextY(double x1, double y1, double x2, double y2, int &x, int &y, double &e, bool first);

public:

    Screen(int width, int height);
    ~Screen();

    int getWidth() { return width; }
    int getHeight() { return height; }

    void addToFrame(std::vector<Pixel>);
    void displayFrame();

    void printValue(int j, std::string value);

    void line(double * p1, double * p2, char c, std::vector<Pixel>* vec);
    void bresenhamLine(double * p1, double * p2, char c, std::vector<Pixel>* vec);
    void bresenhamLine(double x1, double y1, double x2, double y2, char c, std::vector<Pixel>* vec);
    void bresenhamTriangle(double *p1, double *p2, double *p3, char c, std::vector <Pixel> *ve);
    void fillTriangle(double * p1, double * p2, double * p3, char c, std::vector<Pixel>* vec);
    void outlineTriangle(double * p1, double * p2, double * p3, char c, std::vector<Pixel>* vec);

};

#endif //FINAL_PROJECT_SCREEN_HPP
