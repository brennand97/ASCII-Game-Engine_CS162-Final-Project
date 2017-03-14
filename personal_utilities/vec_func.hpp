//
// Created by Brennan on 3/13/2017.
//

#ifndef FINAL_PROJECT_VEC_FUNC_HPP
#define FINAL_PROJECT_VEC_FUNC_HPP

#include <cmath>

namespace douglas {

    const double pi = 3.1415926535897;

    namespace vector {

        double * vector(const double x, const double y);

        double * copy(const double * v);

        double dotProduct(const double * v1, const double * v2);

        double magnitudeCrossProduct(const double * v1, const double * v2);

        double magnitude(const double * v);

        void unitVector(double * v);

        void unitVector(double &x, double &y);

        double angle(const double * v1, const double * v2);

        double * add(const double * v1, const double * v2);

        double * subtract(const double * v1, const double * v2);

        void scale(double * v1, const double c);

        double * project(const double * v, const double * onto);

    }

}

#endif //FINAL_PROJECT_VEC_FUNC_HPP
