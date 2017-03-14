/**
 * Author:      Brennan Douglas
 * Date:        03/05/2017
 * Description: This file is the entry point for the game
 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <atomic>
#include "display/screen.hpp"
#include "game_object.hpp"
#include "spaces/empty_world.hpp"
#include "physics/objects/box.hpp"
#include "player/wheel.hpp"
#include "input.hpp"
#include "personal_utilities/vec_func.hpp"

int main (int argc, char** argv) {

    bool stop = false;

    GameObject::n_obj_id = 0;

    Screen* screen = new Screen(190, 60);
    EmptyWorld* emptyWorld = new EmptyWorld(100.0,50.0);

    Input* input = new Input();
    input->listenTo('q', [&stop, &input](double dt) -> void {
        stop = true;
        input->stop();
    });
    double accel = 20;
    input->listenTo('w', [&emptyWorld, &accel](double dt) -> void {
        double * vel = new double[2];
        vel[0] = 0;
        vel[1] = accel;
        if (dt < 0.1) {
            vel[0] *= dt * dt;
            vel[1] *= dt * dt;
        } else {
            vel[0] *= 0.01;
            vel[1] *= 0.01;
        }
        std::vector<GameObject*> gos;
        emptyWorld->getChildrenOfType(Box::TYPE, &gos);
        std::vector<GameObject*>::iterator it = gos.begin();
        ((Box*) (*it))->addVelocity(vel);
        delete [] vel;
    });
    input->listenTo('s', [&emptyWorld, &accel](double dt) -> void {
        double * vel = new double[2];
        vel[0] = 0;
        vel[1] = -accel;
        if (dt < 0.1) {
            vel[0] *= dt * dt;
            vel[1] *= dt * dt;
        } else {
            vel[0] *= 0.01;
            vel[1] *= 0.01;
        }
        std::vector<GameObject*> gos;
        emptyWorld->getChildrenOfType(Box::TYPE, &gos);
        std::vector<GameObject*>::iterator it = gos.begin();
        ((Box*) (*it))->addVelocity(vel);
        delete [] vel;
    });
    input->listenTo('d', [&emptyWorld, &accel](double dt) -> void {
        std::vector<GameObject*> gos;
        emptyWorld->getChildrenOfType(Wheel::TYPE, &gos);
        std::vector<GameObject*>::iterator it = gos.begin();
        ((Wheel*) (*it))->setAngle(-douglas::pi / 10);
    });
    input->listenTo('a', [&emptyWorld, &accel](double dt) -> void {
        std::vector<GameObject*> gos;
        emptyWorld->getChildrenOfType(Wheel::TYPE, &gos);
        std::vector<GameObject*>::iterator it = gos.begin();
        ((Wheel*) (*it))->setAngle(douglas::pi / 10);
    });
    input->listen();

    std::cout << "Press 'q' to quit." << std::endl;

    emptyWorld->render(screen);
    screen->displayFrame();

    double dt = 0.5;
    std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point start_time = t;

    while (!stop) {

        if(!input->is_multi_threading_enabled()) {
            input->getInput();
        }

        std::vector<GameObject*> children;
        emptyWorld->getChildrenOfType(Particle::TYPE, &children);

        emptyWorld->step(dt);

        emptyWorld->render(screen);
        screen->displayFrame();
        screen->printValue(1, " FPS: " + std::to_string(1/dt));

        std::chrono::high_resolution_clock::time_point nt = std::chrono::high_resolution_clock::now();
        dt = (nt - t).count() / 1000000000.0;
        t = nt;

		if ((t - start_time).count() / 1000000000.0 > 30) {
			//break;
		}
    }

	delete screen;
	delete emptyWorld;
    input->end();
    delete input;

    return 0;

}
