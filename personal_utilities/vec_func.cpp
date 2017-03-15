//
// Created by Brennan on 3/13/2017.
//

#include "vec_func.hpp"

namespace douglas {

    unsigned int factorial(unsigned int n) {
        unsigned int ret = 1;
        for(unsigned int i = 1; i <= n; ++i)
            ret *= i;
        return ret;
    }

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
            double a = std::asin( dotProduct(v1, v2) / ( magnitude(v1) * magnitude(v2) ) );
            double * added = add(v1, v2);
            double * subtracted = subtract(v1, v2);
            if(magnitude(added) < magnitude(subtracted)) {
                a += douglas::pi;
            }
            delete [] added;
            delete [] subtracted;
            return a;
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
