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
    moveCursorVertically(-2);
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

    printLines();
    clearLines();
}

void Screen::printValue(int j, std::string value) {
    std::vector<sideline>::iterator it;
    for(it = sideLines.begin(); it != sideLines.end(); it++) {
        if((*it).n == j) {
            (*it).s = value;
            return;
        }
    }
    sideline sl;
    sl.s = value;
    sl.n = j;
    sl.c_l = value.size();
    sideLines.push_back(sl);
}

void Screen::printLines() {
    std::vector<sideline>::iterator it;
    for(it = sideLines.begin(); it != sideLines.end(); it++) {
        moveCursorVertically(height - (*it).n);
        moveCursorHorizontally(width + 1);
        for(int i = 0; i < (*it).c_l; i++) {
            std::cout << " " << std::flush;
        }
        moveCursorHorizontally( -(*it).c_l );
        std::cout << (*it).s << std::flush;
        (*it).c_l = (*it).s.length();
        moveCursorHorizontally( -width - 1 - (*it).s.length() );
        moveCursorVertically(-height + (*it).n);
    }
}

void Screen::clearLines() {
    std::vector<sideline>::iterator it;
    for(it = sideLines.begin(); it != sideLines.end(); it++) {
        (*it).s = "";
    }
}

void Screen::line(double *p1, double *p2, char c, std::vector<Pixel>* vec) {
    bresenhamLine(p1, p2, c, vec);
}

void Screen::line(const double *p1, const double *p2, char c, std::vector <Pixel> *vec) {
    bresenhamLine(p1[0], p1[1], p2[0], p2[1], c, vec);
}

void Screen::line(double x1, double y1, double x2, double y2, char c, std::vector <Pixel> *vec) {
    bresenhamLine(x1, y1, x2, y2, c, vec);
}

void Screen::bresenhamLine(double *p1, double *p2, char c, std::vector <Pixel> *vec) {

    double x1 = p1[0];
    double y1 = p1[1];
    double x2 = p2[0];
    double y2 = p2[1];

    // Code from https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B

    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if(steep)
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if(x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const double dx = x2 - x1;
    const double dy = fabs(y2 - y1);

    double error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = (int)y1;

    const int maxX = (int)x2;

    for(int x=(int)x1; x<maxX; x++)
    {
        if(steep)
        {
            Pixel p(y, x, c);
            vec->push_back(p);
        }
        else
        {
            Pixel p(x, y, c);
            vec->push_back(p);
        }

        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }

}

void Screen::bresenhamLine(double x1, double y1, double x2, double y2, char c, std::vector <Pixel> *vec) {
    double * p1 = new double[2];
    p1[0] = x1;
    p1[1] = y1;
    double * p2 = new double[2];
    p2[0] = x2;
    p2[1] = y2;
    bresenhamLine(p1, p2, c, vec);
    delete [] p1;
    delete [] p2;
}

void Screen::outlineTriangle(double *p1, double *p2, double *p3, char c, std::vector <Pixel> *vec) {
    bresenhamLine(p1, p2, c, vec);
    bresenhamLine(p2, p3, c, vec);
    bresenhamLine(p3, p1, c, vec);
}