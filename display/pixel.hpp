/**
 * Author:      Brennan Douglas
 * Date:        03/07/2017
 * Description: This file holds the Pixel class which is used to hold a char at a point of the screen
 */

#ifndef FINAL_PROJECT_PIXEL_HPP
#define FINAL_PROJECT_PIXEL_HPP

// This class is used to be a representation of a char at a particular integer coordinate on the screen
class Pixel {
protected:
    int i;      // i represents the column
    int j;      // j represents the row
    char c;     // c is the char that will be printed there
public:
    // Basic constructor with default char
    Pixel(int i, int j) : Pixel(i, j, ' ') {}
    // Full constructor with arbitrary char
    Pixel(int i, int j, char c) {
        this->i = i;
        this->j = j;
        this->c = c;
    }
    // Returns the column
    int getI() { return i; }
    // Returns the row
    int getJ() { return j; }
    // Returns the char being printed
    char getChar() { return c; }
    // Updates the char that will be printed
    void setChar(char c) { this->c = c; }
    // Checks equality with another Pixel by ixj only not the char
    bool operator ==(const Pixel& other) { return (i == other.i) && (j == other.j); }
    bool operator !=(const Pixel& other) { return !(*this == other); }

    // This is used to sort the pixels from low to high column values when in a vector
    struct i_low_to_high {
        inline bool operator() (const Pixel& p1, const Pixel& p2) {
            return (p1.i < p2.i);
        }
    };

    // This is used to sort the pixels from low to high row values when in a vector
    struct j_low_to_high {
        inline bool operator() (const Pixel& p1, const Pixel& p2) {
            return (p1.j < p2.j);
        }
    };

};

#endif //FINAL_PROJECT_PIXEL_HPP
