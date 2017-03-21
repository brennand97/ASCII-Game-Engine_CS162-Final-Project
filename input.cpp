/**
 * Author:      Brennan Douglas
 * Date:        03/11/2017
 * Description: This is the source file for the Input class
 */

#include "input.hpp"
#include "linux_input.hpp"
#include <algorithm>
#include <iostream>

// Input Constructor
Input::Input() {
    stop_trigger = false;
}

// Input Deconstructor
Input::~Input() {
    end();
    if(thread != nullptr) {
        delete thread;
    }
}

// Add a char that is being listened for with a callback to accompany it
void Input::listenTo(char c, v_d_callback callback) {
    Key c_key(c, callback);
    keys.push_back(c_key);
}

// Stop listening to the keyboard for input
void Input::stop() {
    stop_trigger = true;
}

// Cleanly end the input class
void Input::end() {
    if(multi_threading && thread->joinable()) {
        thread->join();
    } else {
        std::ios_base::sync_with_stdio(true);
    }
    resetTermios();
}

// Start to listen to the keyboard for input
bool Input::listen() {
    try {
        thread = new std::thread(&Input::loop, std::ref(*this));
        thread->detach();
    } catch ( std::exception e ) {
        // OSU ENGR Flip server doesn't have multi-threading :( such a shame
        multi_threading = false;
        std::ios_base::sync_with_stdio(false);
    }
    initTermios(0);

    return multi_threading;
}

// Retrieve input from the keyboard
void Input::getInput() {
    if(multi_threading || (std::cin.rdbuf() && std::cin.rdbuf()->in_avail() > 0)) {
        char c = getchar();
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

// Loop function for multi-threading
void Input::loop() {
    while (!stop_trigger && multi_threading) {
        getInput();
    }
}

// Manually disable multi_threading if desired
void Input::disable_multi_threading(bool b) {
    multi_threading = !b;
}
