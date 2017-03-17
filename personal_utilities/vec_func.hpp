//
// Created by Brennan on 3/13/2017.
//

#ifndef FINAL_PROJECT_VEC_FUNC_HPP
#define FINAL_PROJECT_VEC_FUNC_HPP

#include <cmath>
#include <stdexcept>

namespace douglas {

    const double pi = 3.1415926535897;

    unsigned int factorial(unsigned int n);

    int sign(const double d);

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

        double * intersection(const double * l1_p1,
                                 const double * l1_p2,
                                 const double * l2_p1,
                                 const double * l2_p2);

    }

}

#endif //FINAL_PROJECT_VEC_FUNC_HPP
