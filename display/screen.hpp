//
// Created by Brennan on 3/7/2017.
//

#ifndef FINAL_PROJECT_SCREEN_HPP
#define FINAL_PROJECT_SCREEN_HPP

#include <vector>

class Screen {
public:

    struct Pixel {
        int i;
        int j;
        char c;
        Pixel(int i, int j, int c) {
            this->i = i;
            this->j = j;
            this->c = c;
        }
    };

protected:
    bool first_frame = false;
    std::vector<Pixel> previous_frame;
    std::vector<Pixel> frame;
public:

    Screen(int width, int height);

    void newFrame();
    std::vector<Pixel> pullFrame();
    std::vector<Pixel> pullDeltaFrame();

};

#endif //FINAL_PROJECT_SCREEN_HPP
