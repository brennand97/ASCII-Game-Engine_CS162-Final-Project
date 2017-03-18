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

    int sign(const double d) {
        if (d > 0) {
            return 1;
        } else if (d < 0) {
            return -1;
        } else {
            return 0;
        }
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

        double * intersection(const double * l1_p1,
                              const double * l1_p2,
                              const double * l2_p1,
                              const double * l2_p2) {

            // Make sure both lines' x-component progress in the positive direction
            if (l1_p1[0] > l1_p2[0]) {
                return intersection(l1_p2, l1_p1, l2_p1, l2_p2);
            } else if (l2_p1[0] > l2_p2[0]) {
                return intersection(l1_p1, l1_p2, l2_p2, l2_p1);
            }

            if ( l1_p1[0] == l1_p2[0] && l2_p1[0] == l2_p2[0] ) {
                // Both vertical lines
                throw std::out_of_range("Both line segments are vertical lines");
            } else if ( l1_p1[0] == l1_p2[0] ) {
                // To decrease writing the same code twice
                return intersection(l2_p1, l2_p2, l1_p1, l1_p2);
            } else if ( l2_p1[0] == l2_p2[0] ) {

                // Make sure y progresses in the positive direction
                if ( l2_p1[1] > l2_p2[1] ) {
                    return intersection(l1_p1, l1_p2, l2_p2, l2_p1);
                }

                // Handle a single vertical line
                double m1 = (l1_p2[1] - l1_p1[1]) / (l1_p2[0] - l1_p1[0]);

                double t1 = l2_p1[0] - l1_p1[0];
                double t2 = (m1 * t1) + l1_p1[1] - l2_p1[1];

                if ( t1 < 0 || t1 > (l1_p2[0] - l1_p1[0])
                     || t2 < 0 || t2 > (l2_p2[1] - l2_p1[1])) {
                    // The line segments do not cross
                    throw std::out_of_range("The line segments do not cross");
                } else {
                    return vector(l2_p1[0], t2 + l2_p1[1]);
                }

            } else {
                // Handle two none vertical lines
                double m1 = (l1_p2[1] - l1_p1[1]) / (l1_p2[0] - l1_p1[0]);
                double m2 = (l2_p2[1] - l2_p1[1]) / (l2_p2[0] - l2_p1[0]);

                if ( m1 == m2 ) {
                    // The lines are parallel and never meet
                    throw std::out_of_range("The lines are parallel and never meet");
                }

                double t2 = ((l2_p1[1] - l1_p1[1]) - (m1 * (l2_p1[0] - l1_p1[0]))) / (m1 - m2);
                double t1 = t2 + l2_p1[0] - l1_p1[0];

                if ( t1 < 0 || t1 > (l1_p2[0] - l1_p1[0])
                     || t2 < 0 || t2 > (l2_p2[0] - l2_p1[0])) {
                    // The line segments do not cross
                    throw std::out_of_range("The line segments do not cross");
                } else {
                    return vector(t1 + l1_p1[0], (m1 * t1) + l1_p1[1]);
                }
            }

        }

    }

}
