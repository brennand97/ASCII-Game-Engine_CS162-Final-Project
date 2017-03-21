/**
 * Author:      Brennan Douglas
 * Date:        03/14/2017
 * Description: This is the header file for the ConvexPolygon class
 */

#ifndef FINAL_PROJECT_CONVEX_POLYGON_HPP
#define FINAL_PROJECT_CONVEX_POLYGON_HPP

#include "../particle_container.hpp"
#include "../../personal_utilities/vec_func.hpp"
#include "../constraints/single_constraint.hpp"
#include "../constraints/line_constraint.hpp"

// ConvexPolygon is a generalization of all Convex Polygons
class ConvexPolygon : public ParticleContainer {

public:
    class ConvexPolygonConstraint : public SingleConstraint {
    private:
        ConvexPolygon* polygon;
    public:
        ConvexPolygonConstraint(ConvexPolygon* polygon);
        void fix(int iter, Particle* p);
    };

protected:

    int num_vertices;
    std::vector<Particle*> vertices;
    bool solid;
    double rigid;
    ConvexPolygonConstraint* solid_constraint;
    std::vector<LineConstraint*> line_constraints;

    void setConstraints();

public:

    static std::string TYPE;

    ConvexPolygon(bool solid = true, double rigid = 1);
    ConvexPolygon(std::vector<Particle*> vertices, bool solid = true, double rigid = 1);

    void render(Screen* screen);

};

#endif //FINAL_PROJECT_CONVEX_POLYGON_HPP
