/**
 * Author:      Brennan Douglas
 * Date:        03/05/2017
 * Description: This file is the entry point for the game
 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "display/screen.hpp"
#include "game_object.hpp"
#include "spaces/empty_world.hpp"
#include "input.hpp"

int main (int argc, char** argv) {

    GameObject::n_obj_id = 0;

    EmptyWorld* emptyWorld = new EmptyWorld(50,25,50,25);
    emptyWorld->setup();

    double dt = 0.5;
    std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();

    int i = 0;
    while (true) {

        std::vector<GameObject*> children;
        emptyWorld->getChildrenOfType(Particle::TYPE, &children);

        i++;
//        std::cout << std::endl;
//        std::cout << "i: " << i << std::endl;
//        std::cout << "Particle 1: (" << (*((Particle*) children[0]))[0] << ", " << (*((Particle*) children[0]))[1] << ")" << std::endl;
//        std::cout << "Particle 2: (" << (*((Particle*) children[1]))[0] << ", " << (*((Particle*) children[1]))[1] << ")" << std::endl;
//        std::cout << "Dist: " << Constraint::dist((Particle*) children[0], (Particle*) children[1]) << std::endl;

        emptyWorld->step(dt);

        emptyWorld->render();

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        std::chrono::high_resolution_clock::time_point nt = std::chrono::high_resolution_clock::now();
        dt = (nt - t).count() / 1000000000.0;
        t = nt;
    }

    /*
    Particle* p1 = new Particle();

    double * ppos2 = new double[2];
    double * vel2 = new double[2];
    ppos2[0] = 11;
    ppos2[1] = 0;
    vel2[0] = 0;
    vel2[1] = 2;
    Particle* p2 = new Particle(ppos2, vel2);

    LineConstraint lc(10, Constraint::Equality::EQUAL);
    DragConstraint dc(0.3);

    double dt = 0.5;
    std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();

    int i = 0;
    while (true) {
        i++;
        std::cout << std::endl;
        std::cout << "i: " << i << std::endl;
        std::cout << "Particle 1: (" << (*p1)[0] << ", " << (*p1)[1] << ")" << std::endl;
        std::cout << "Particle 2: (" << (*p2)[0] << ", " << (*p2)[1] << ")" << std::endl;
        std::cout << "Dist: " << Constraint::dist(p1, p2) << std::endl;

        p1->step(dt);
        p2->step(dt);

        for(int i = 0; i < 5; i++) {
            dc.fix(i + 1, p1);
            dc.fix(i + 1, p2);
            lc.fix(i + 1, p1, p2);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::chrono::high_resolution_clock::time_point nt = std::chrono::high_resolution_clock::now();
        dt = (nt - t).count() / 1000000000.0;
        t = nt;
    }

    delete p1;
    delete p2;

    */

    return 0;

}