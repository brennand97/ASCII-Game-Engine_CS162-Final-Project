//
// Created by Brennan on 3/8/2017.
//

#ifndef FINAL_PROJECT_PIXEL_HPP
#define FINAL_PROJECT_PIXEL_HPP

class Pixel {
protected:
    int i;
    int j;
    char c;
public:
    Pixel(int i, int j) : Pixel(i, j, ' ') {}
    Pixel(int i, int j, char c) {
        this->i = i;
        this->j = j;
        this->c = c;
    }
    int getI() { return i; }
    int getJ() { return j; }
    char getChar() { return c; }
    void setChar(char c) { this->c = c; }
    bool operator ==(const Pixel& other) { return (i == other.i) && (j == other.j); }
    bool operator !=(const Pixel& other) { return !(*this == other); }

    struct i_low_to_high {
        inline bool operator() (const Pixel& p1, const Pixel& p2) {
            return (p1.i < p2.i);
        }
    };

    struct j_low_to_high {
        inline bool operator() (const Pixel& p1, const Pixel& p2) {
            return (p1.j < p2.j);
        }
    };

};

#endif //FINAL_PROJECT_PIXEL_HPP
