/**
 * Author:      Brennan Douglas
 * Date:        03/07/2017
 * Description: This file holds the source code for the screen class
 */

#include "screen.hpp"
#include <algorithm>
#include <cmath>
#include <chrono>

// Default constructor, the pixel width and height are the defining factors of a screen
Screen::Screen(int width, int height) {
    this->width = width;
    this->height = height;
    previous_frame = nullptr;
    frame = nullptr;
    // Initialize both the frame and the previous frame by calling newFrame twice
    newFrame();
    newFrame();
}

// Deconstructor, free up any memory and reset the cursor position
Screen::~Screen() {
    // Move the cursor back to its normal location
    moveCursorVertically(-2);
    // Free up the memory from frame and previous_frame
    delete frame;
    delete previous_frame;
}

// Moves the cursor vertically by j, when positive it goes up and negative goes down
void Screen::moveCursorVertically(int j) {
    if(j > 0) {
        // ASCII control sequence for upwards
        std::cout << "\033[" << j << "A" << std::flush;
    } else if(j < 0) {
        // ASCII control sequence for downwards
        std::cout << "\033[" << -j << "B" << std::flush;
    }
}

// Moves the cursor horizontally by i, when positive it goes to the right and negative goes to the left
void Screen::moveCursorHorizontally(int i) {
    if(i > 0) {
        // ASCII control sequence for rightward movement
        std::cout << "\033[" << i << "C" << std::flush;
    } else if (i < 0) {
        // ASCII control sequence for leftward movement=
        std::cout << "\033[" << -i << "D" << std::flush;
    }
}

// This handles the creation of a new frame and the deletion of the prior previous one
void Screen::newFrame() {
    // Delete the old previous frame
    delete previous_frame;
    // Set the current frame to the previous frame
    previous_frame = frame;
    // Create a new frame
    frame = new std::vector<Pixel>();
    // Fill the new frame with default (empty) pixels
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            Pixel p(i,j);
            frame->push_back(p);
        }
    }
}

// Calculate the difference between the frame and the previous frame to decrease how much is needed to print to
// the terminal since it is slow.  This also decrease the required bandwidth if being displayed over ssh.
std::vector<Pixel> Screen::pullDeltaFrame() {
    // Define return pixel vector
    std::vector<Pixel> delta;
    // For every pixel check to see if the char value is different between frame and previous frame
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            int index = i + (j * width);
            if((*frame)[index].getChar() != (*previous_frame)[index].getChar()) {
                // If they chars are different add the new pixel to the output pixel vector
                delta.push_back((*frame)[index]);
            }
        }
    }
    // Sort the output vector to optimize how the pixels are printed to the screen
    // Sort the output vector from smallest to largest i
    std::sort(delta.begin(), delta.end(), Pixel::i_low_to_high());
    // Sort the output vector from smallest to largest j
    std::sort(delta.begin(), delta.end(), Pixel::j_low_to_high());
    // Return the output vector
    return delta;
}

// Add a vector of pixels to the current frame, overwriting previous char values for those pixels
void Screen::addToFrame(std::vector <Pixel> add) {
    std::vector<Pixel>::iterator it;
    // Loop through each picture
    for(it = add.begin(); it != add.end(); it++) {
        // Check to make sure the pixel is inside the screen
        if((*it).getI() >= 0 && (*it).getI() < width && (*it).getJ() >= 0 && (*it).getJ() < height) {
            // Update the current frames pixel value to the supplied value.
            // This assumes that the frame pixel vector has order to it's pixels, e.g. rows together.
            (*frame)[(*it).getI() + (width * (*it).getJ())].setChar((*it).getChar());
        }
    }
}

// This function displays the current frame
void Screen::displayFrame() {
    std::vector<Pixel> v_frame;
    // If the screen has not been drawn before draw the entirety of the previous frame
    if(first_frame) {
        first_frame = false;
        v_frame = *previous_frame;
        for(int j = height; j >= -1; j--) {
            for(int i = -1; i <= width; i++) {
                if(i >= 0 && i < width && j >= 0 && j < height) {
                    // Print the char value at the ixj coordinate
                    int index = i + (j * width);
                    std::cout << v_frame[index].getChar();
                } else {
                    // Draw a frame around the screen
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
                // Set the cursor up for printed the delta frame
                std::cout << std::flush;
                moveCursorVertically(1);
                moveCursorHorizontally(-width - 1);
            }
        }
    }

    // The cursor is assumed to be at the bottom left-hand corner.
    // The only reason this would not be true is if there was something externally typed.
    int p_i = 0;
    int p_j = 0;
    // Calculate the delta frame
    v_frame = pullDeltaFrame();
    // Loop through all the pixels in the delta frame
    for(unsigned int i = 0; i < v_frame.size(); i++) {
        Pixel p = v_frame[i];
        // Find the difference in rows and columns to get to the current pixel value from where the cursor currently is.
        int d_i = p.getI() - p_i;
        int d_j = p.getJ() - p_j;
        // Move the cursor to the current pixel location
        moveCursorHorizontally(d_i);
        moveCursorVertically(d_j);
        // Print the char out at that location
        std::cout << p.getChar() << std::flush;
        // Update the current cursor position
        p_i = p.getI() + 1;
        p_j = p.getJ();
        // While the next pixel is adjacent to this pixel
        while ((i + 1) < v_frame.size() &&
                v_frame[i + 1].getI() == p_i &&
                v_frame[i + 1].getJ() == p_j) {
            i++;
            // Print out the char
            std::cout << v_frame[i].getChar() << std::flush;
            // Update the cursor position
            p_i++;
        }
    }
    // Move the cursor back to the bottom left corner
    moveCursorHorizontally( -p_i );
    moveCursorVertically( -p_j );

    // Create a new frame
    newFrame();

    // Print any lines that the user has given the screen
    printLines();
    // Clear this frame's set of lines
    clearLines();

}

// Print a value on the right side of the screen at a specified row for this frame.
void Screen::printValue(int j, std::string value) {
    std::vector<sideline>::iterator it;
    // Check to see if there is already a sideLine at that row
    for(it = sideLines.begin(); it != sideLines.end(); it++) {
        if((*it).n == j) {
            // If one already exists just update its value and return
            (*it).s = value;
            return;
        }
    }
    // If one doesn't already exist create one and add it
    sideline sl;
    sl.s = value;
    sl.n = j;
    sl.c_l = value.size();
    sideLines.push_back(sl);
}

// Print the lines provided by the user for the right side of the screen
void Screen::printLines() {
    std::vector<sideline>::iterator it;
    // Loop through each sideLine
    for(it = sideLines.begin(); it != sideLines.end(); it++) {
        // Move the cursor to the specified position
        moveCursorVertically(height - (*it).n);
        moveCursorHorizontally(width + 1);
        // Clear the line of the previous value
        for(int i = 0; i < (*it).c_l; i++) {
            std::cout << " " << std::flush;
        }
        // Move the cursor back to the start of the line
        moveCursorHorizontally( -(*it).c_l );
        // Print out the value
        std::cout << (*it).s << std::flush;
        // Update the clean_length value, so it is known how much needs to be erased
        (*it).c_l = (*it).s.length();
        // Move the cursor back to the bottom left corner of the screen
        moveCursorHorizontally( -width - 1 - (*it).s.length() );
        moveCursorVertically(-height + (*it).n);
    }
}

// Clear the lines provided for the right hand side of the screen
void Screen::clearLines() {
    std::vector<sideline>::iterator it;
    for(it = sideLines.begin(); it != sideLines.end(); it++) {
        (*it).s = "";
    }
}

// Helper function for bresenhamLine
void Screen::line(double *p1, double *p2, char c, std::vector<Pixel>* vec) {
    bresenhamLine(p1, p2, c, vec);
}

// Helper function for bresenhamLine
void Screen::line(const double *p1, const double *p2, char c, std::vector <Pixel> *vec) {
    bresenhamLine(p1[0], p1[1], p2[0], p2[1], c, vec);
}

// Helper function for bresenhamLine
void Screen::line(double x1, double y1, double x2, double y2, char c, std::vector <Pixel> *vec) {
    bresenhamLine(x1, y1, x2, y2, c, vec);
}

// Line rasterization algorithm
void Screen::bresenhamLine(double *p1, double *p2, char c, std::vector <Pixel> *vec) {

    double x1 = p1[0];
    double y1 = p1[1];
    double x2 = p2[0];
    double y2 = p2[1];

    // Code modified from https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B

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

// Helper function for bresenhamLine
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

// Helper function for creating the outline of a triangle
void Screen::outlineTriangle(double *p1, double *p2, double *p3, char c, std::vector <Pixel> *vec) {
    bresenhamLine(p1, p2, c, vec);
    bresenhamLine(p2, p3, c, vec);
    bresenhamLine(p3, p1, c, vec);
}