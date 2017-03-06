//
// Created by Brennan on 3/6/2017.
//

#include "box.hpp"

Box::Box(double *pos, double width, double height) : GameObject(pos, nullptr) {
    hit[0] = width;
    hit[1] = height;

    double h_w = width / 2;
    double h_h = height / 2;

    double * pos1 = new double[2];
    pos1[0] = - h_w;
    pos1[1] = h_h;
    double * pos2 = new double[2];
    pos2[0] = h_w;
    pos2[1] = h_h;
    double * pos3 = new double[2];
    pos3[0] = h_w;
    pos3[1] = - h_h;
    double * pos4 = new double[2];
    pos4[0] = - h_w;
    pos4[1] = - h_h;
}

void Box::render() {

}