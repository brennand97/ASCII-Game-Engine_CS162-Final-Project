//
// Created by Brennan on 3/13/2017.
//

#ifndef FINAL_PROJECT_VEC_FUNC_HPP
#define FINAL_PROJECT_VEC_FUNC_HPP

#include <cmath>

namespace douglas {

    namespace vector {

        double * vector(const double x, const double y) {
            double * out = new double[2];
            out[0] = x;
            out[1] = y;
            return out;
        }

        double * copy(const double * v) {
            return vector(v[0], v[1]);
        }

        double dotProduct(const double * v1, const double * v2) {
            return (v1[0] * v2[0]) + (v1[1] * v2[1]);
        }

        double magnitudeCrossProduct(const double * v1, const double * v2) {
            return (v1[0] * v2[1]) - (v1[1] * v2[0]);
        }

        double magnitude(const double * v) {
            return std::sqrt(dotProduct(v, v));
        }

        void unitVector(double * v) {
            double mag = magnitude(v);
            v[0] /= mag;
            v[1] /= mag;
        }

        void unitVector(double &x, double &y) {
            double * vec = vector(x, y);
            double mag = magnitude(vec);
            delete [] vec;
            x /= mag;
            y /= mag;
        }

        double angle(const double * v1, const double * v2) {
            return std::asin( dotProduct(v1, v2) / ( magnitude(v1) * magnitude(v2) ) );
        }

        double * add(const double * v1, const double * v2) {
            double * out = new double[2];
            out[0] = v1[0] + v2[0];
            out[1] = v1[1] + v2[1];
            return out;
        }

        double * subtract(const double * v1, const double * v2) {
            double * out = new double[2];
            out[0] = v1[0] - v2[0];
            out[1] = v1[1] - v2[1];
            return out;
        }

        void scale(double * v1, const double c) {
            v1[0] *= c;
            v1[1] *= c;
        }

        double * project(const double * v, const double * onto) {
            double * out = copy(onto);
            double mag2 = magnitude(onto);
            scale(out, dotProduct(v, onto) / (mag2 * mag2));
            return out;
        }

    }

}

#endif //FINAL_PROJECT_VEC_FUNC_HPP
