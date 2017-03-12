//
// Created by Brennan on 3/11/2017.
//

#include "input.hpp"
#include "linux_input.hpp"
#include <algorithm>
#include <iostream>

Input::Input() {
    stop_trigger = false;
}

Input::~Input() {
    if(thread != nullptr) {
        delete thread;
    }
}

void Input::listenTo(char c, v_d_callback callback) {
    Key c_key(c, callback);
    keys.push_back(c_key);
}

void Input::stop() {
    stop_trigger = true;
}

void Input::end() {
    if(multi_threading && thread->joinable()) {
        thread->join();
    }
}

bool Input::listen() {
    try {
        thread = new std::thread(&Input::loop, std::ref(*this));
        thread->detach();
    } catch ( std::system_error e ) {
        // OSU ENGR Flip server doesn't have multi-threading :( such a shame
        multi_threading = false;
    }

    return multi_threading;

}

void Input::getInput() {
    if(multi_threading || (std::cin.rdbuf() && std::cin.rdbuf()->in_avail() >= 0)) {
        char c = getch();
        std::vector<Key>::iterator it;
        it = std::find(keys.begin(), keys.end(), c);
        if(it != keys.end()) {
            std::chrono::high_resolution_clock::time_point c_time_point = std::chrono::high_resolution_clock::now();
            try {
                (*it).callback((double) ((c_time_point - (*it).last_seen).count() / 1000000000.0));
            } catch ( std::bad_function_call e ) {
                // Do nothing
            }
            (*it).last_seen = c_time_point;
        }
    }
}

void Input::loop() {
    while (!stop_trigger && multi_threading) {
        getInput();
    }
}