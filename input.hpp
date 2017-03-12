//
// Created by Brennan on 3/5/2017.
//

#ifndef FINAL_PROJECT_INPUT_HPP
#define FINAL_PROJECT_INPUT_HPP

#include <vector>
#include <functional>
#include <thread>
#include <chrono>
#include <atomic>

class Input {
    using v_d_callback = std::function<void(double)>;
private:
    struct Key {
        char k;
        v_d_callback callback;
        std::chrono::high_resolution_clock::time_point last_seen;
        Key(char k, v_d_callback callback) {
            this->k = k;
            this->callback = callback;
            this->last_seen = std::chrono::high_resolution_clock::now();
        }
        bool operator==(const char& c) { return this->k == c; }
        bool operator!=(const char& c) { return !(*this == c); }
    };
    std::vector<Key> keys;
    std::thread* thread = nullptr;
    bool stop_trigger;
    void loop();
public:
    Input();
    ~Input();

    void listenTo(char c, v_d_callback callback);

    void stop();
    void end();
    void listen();
};

#endif //FINAL_PROJECT_INPUT_HPP
