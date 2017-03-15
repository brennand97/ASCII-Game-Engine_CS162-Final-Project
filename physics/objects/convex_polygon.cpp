//
// Created by Brennan on 3/14/2017.
//

#include "convex_polygon.hpp"
#include "../../spaces/space.hpp"
#include <cmath>

std::string ConvexPolygon::TYPE = "convex_polygon";

ConvexPolygon::ConvexPolygon(bool solid, double rigid) {
    addType(ConvexPolygon::TYPE);
    this->solid = solid;
    this->rigid = rigid;
    solid_constraint = new ConvexPolygon::ConvexPolygonConstraint(this);
    addSuperGlobalConstraint(solid_constraint);
}

ConvexPolygon::ConvexPolygon(std::vector<Particle*> vertices, bool solid, double rigid) : ParticleContainer() {
    addType(ConvexPolygon::TYPE);
    for(unsigned int i = 0; i < vertices.size(); i++) {
        addChild(vertices[i]);
    }
    this->vertices = vertices;
    this->num_vertices = vertices.size();
    this->solid = solid;
    this->rigid = rigid;
    solid_constraint = new ConvexPolygon::ConvexPolygonConstraint(this);
    addSpecificConstraint(solid_constraint);

    // Hold them in the place they were initialized
    setConstraints();
}

void ConvexPolygon::setConstraints() {
    for(int i = 0; i < num_vertices; i++) {
        for(int j = i + 1; j < num_vertices; j++) {
            double * dist = douglas::vector::subtract(
                    vertices[i]->getPosition(),
                    vertices[j]->getPosition()
            );
            LineConstraint* lc = new LineConstraint(douglas::vector::magnitude(dist), Constraint::EQUAL);
            lc->addParticle(vertices[i]);
            lc->addParticle(vertices[j]);
            line_constraints.push_back(lc);
            addSpecificConstraint(lc);
        }
    }
}

void ConvexPolygon::render(Screen *screen) {
    Space* world = (Space*) getWorld();
    double * p_pos = world->convertToPixels(vertices[0]->getPosition(), screen);
    double * pos;
    for(unsigned i = 1; i < vertices.size(); i++) {
        pos = world->convertToPixels(vertices[i]->getPosition(), screen);
        std::vector<Pixel> line;
        screen->line(pos, p_pos, draw_char, &line);
        screen->addToFrame(line);
        delete [] p_pos;
        p_pos = pos;
    }
    pos = world->convertToPixels(vertices[0]->getPosition(), screen);
    std::vector<Pixel> line;
    screen->line(pos, p_pos, draw_char, &line);
    screen->addToFrame(line);
    delete [] p_pos;
    delete [] pos;
}

ConvexPolygon::ConvexPolygonConstraint::ConvexPolygonConstraint(ConvexPolygon *polygon) {
    this->polygon = polygon;
}

void ConvexPolygon::ConvexPolygonConstraint::fix(int iter, Particle *p) {

    if(this->polygon->solid) {

        // TODO this could do with a limiting factor to decrease calculation time for non-effected particles

        int min_index = 0;
        double total_angle = 0;
        double *p_vec = douglas::vector::subtract(this->polygon->vertices[0]->getPosition(),
                                                  p->getPosition());
        double *min_vec = p_vec;
        for (int i = 1; i < this->polygon->num_vertices; i++) {
            double *vec = douglas::vector::subtract(this->polygon->vertices[i]->getPosition(),
                                                    p->getPosition());
            total_angle += douglas::vector::angle(p_vec, vec);
            if (douglas::vector::magnitude(vec) < douglas::vector::magnitude(min_vec)) {
                *min_vec = *vec;
                min_index = i;
            }
            *p_vec = *vec;
        }

        if (total_angle > douglas::pi) {
            // Particle is inside the polygon

            // Find the adjacent closest vertex
            // The final second minimum
            double *min2_vec;
            // The index greater then min
            double *ming_vec = douglas::vector::subtract(
                    this->polygon->vertices[(min_index + 1) % this->polygon->num_vertices]->getPosition(),
                    p->getPosition());
            // The index less then min
            double *minl_vec = douglas::vector::subtract(
                    this->polygon->vertices[(min_index + this->polygon->num_vertices - 1) % this->polygon->num_vertices]->getPosition(),
                    p->getPosition());
            if (douglas::vector::magnitude(ming_vec) > douglas::vector::magnitude(minl_vec)) {
                min2_vec = minl_vec;
                delete[] ming_vec;
            } else {
                min2_vec = ming_vec;
                delete[] minl_vec;
            }

            // Find shortest exit path
            // This is done using vector projection onto a line (Vector Math)
            double *edge = douglas::vector::subtract(min2_vec, min_vec);
            double *min_to_point = douglas::vector::subtract(p->getPosition(), min_vec);
            double *proj = douglas::vector::project(min_to_point, edge);
            // This is the shortest exit path of the particle
            double *exit_path = douglas::vector::subtract(proj, min_to_point);
            // Scale for rigidness
            douglas::vector::scale(exit_path, this->polygon->rigid);

            // New particle position
            double *n_pos = douglas::vector::add(p->getPosition(), exit_path);
            // Set new particle position
            p->setPosition(n_pos);

            delete[] min2_vec;
            delete[] edge;
            delete[] min_to_point;
            delete[] proj;
            delete[] exit_path;
            delete[] n_pos;
        }

        if(min_vec != p_vec) {
            delete [] min_vec;
        }
        delete[] p_vec;

    }

}