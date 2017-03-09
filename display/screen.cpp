//
// Created by Brennan on 3/7/2017.
//

#include "screen.hpp"
#include <algorithm>
#include <cmath>

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
        std::cout << "\033[" << j << "A" << std::flush;
    } else if(j < 0) {
        std::cout << "\033[" << -j << "B" << std::flush;
    }
}

void Screen::moveCursorHorizontally(int i) {
    if(i > 0) {
        std::cout << "\033[" << i << "C" << std::flush;
    } else if (i < 0) {
        std::cout << "\033[" << -i << "D" << std::flush;
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
            if((*frame)[index].getChar() != (*previous_frame)[index].getChar()) {
                delta.push_back((*frame)[index]);
            }
        }
    }
    return delta;
}

void Screen::addToFrame(std::vector <Pixel> add) {
    std::vector<Pixel>::iterator it;
    for(it = add.begin(); it != add.end(); it++) {
        if((*it).getI() >= 0 && (*it).getI() < width && (*it).getJ() >= 0 && (*it).getJ() < height) {
            (*std::find(frame->begin(), frame->end(), *it)).setChar((*it).getChar());
        }
    }
}

void Screen::displayFrame() {
    std::vector<Pixel> v_frame;
    if(first_frame) {
        first_frame = false;
        v_frame = *previous_frame;
        for(int j = height; j >= -1; j--) {
            for(int i = -1; i <= width; i++) {
                if(i >= 0 && i < width && j >= 0 && j < height) {
                    int index = i + (j * width);
                    std::cout << v_frame[index].getChar();
                } else {
                    if(i == -1 || i == width) {
                        if(j == -1) {
                            if( i == -1) {
                                std::cout << '\\';
                            } else {
                                std::cout << '/';
                            }
                        } else if(j == height) {
                            if( i == -1) {
                                std::cout << '/';
                            } else {
                                std::cout << '\\';
                            }
                        } else {
                            std::cout << '|';
                        }
                    } else {
                        std::cout << '-';
                    }
                }
            }
            if(j != -1) {
                std::cout << std::endl;
            } else {
                std::cout << std::flush;
                moveCursorVertically(1);
                moveCursorHorizontally(-width - 1);
            }
        }
    }

    int p_i = 0;
    int p_j = 0;
    v_frame = pullDeltaFrame();
    for(unsigned int i = 0; i < v_frame.size(); i++) {
        //TODO this could use some optimizing
        Pixel p = v_frame[i];
        int d_i = p.getI() - p_i;
        int d_j = p.getJ() - p_j;
        moveCursorHorizontally(d_i);
        moveCursorVertically(d_j);
        std::cout << p.getChar() << std::flush;
        p_i = p.getI() + 1;
        p_j = p.getJ();
    }
    moveCursorHorizontally( -p_i );
    moveCursorVertically( -p_j );

    newFrame();
}

void Screen::printValue(int j, std::string value) {
    moveCursorVertically(height - j);
    moveCursorHorizontally(width + 1);
    std::cout << value << std::flush;
    moveCursorHorizontally( -width - 1 - value.length() );
    moveCursorVertically(-height + j);
}

void Screen::getLine(double *p1, double *p2, char c, std::vector<Pixel>* vec) {
    double l = std::sqrt(((p2[0] - p1[0])*(p2[0] - p1[0])) + ((p2[1] - p1[1])*(p2[1] - p1[1])));
    double m = (p2[1] - p1[1]) / (p2[0] - p1[0]);
    bool vert = (p2[0] - p1[0]) == 0;
    double s = 0;
    double t_sign = (p2[0] - p1[0]) > 0 ? 1.0 : -1.0;
    while (s < l) {
        double t;
        if(vert) {
            t = t_sign * s;
        } else {
            t = t_sign * s / std::sqrt(1+(m*m));
        }
        s += 1;
        double x, y;
        if(vert) {
            x = p1[0];
            y = t + p1[1];
        } else {
            x = t + p1[0];
            y = (m * t) + p1[1];
        }
        int i = x;
        int j = y;
        Pixel p(i, j, c);
        if (vec->size() == 0 || (*vec)[vec->size() - 1] != p) {
            vec->push_back(p);
        }
    }
}

void Screen::fillTriangle(double *p1, double *p2, double *p3, char c, std::vector <Pixel> *vec) {
    double l = std::sqrt(((p2[0] - p1[0])*(p2[0] - p1[0])) + ((p2[1] - p1[1])*(p2[1] - p1[1])));
    double m = (p2[1] - p1[1]) / (p2[0] - p1[0]);
    bool vert = (p2[0] - p1[0]) == 0;
    double s = 0;
    double t_sign = (p2[0] - p1[0]) > 0 ? 1.0 : -1.0;
    while (s < l) {
        double t;
        if(vert) {
            t = t_sign * s;
        } else {
            t = t_sign * s / std::sqrt(1+(m*m));
        }
        s += 0.8;
        double * p4 = new double[2];
        if(vert) {
            p4[0] = p1[0];
            p4[1] = t + p1[1];
        } else {
            p4[0] = t + p1[0];
            p4[1] = (m * t) + p1[1];
        }
        getLine(p3, p4, c, vec);
        delete [] p4;
    }
}

void Screen::outlineTriangle(double *p1, double *p2, double *p3, char c, std::vector <Pixel> *vec) {
    getLine(p1, p2, c, vec);
    getLine(p2, p3, c, vec);
    getLine(p3, p1, c, vec);
}