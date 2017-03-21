/**
 * Author:      Brennan Douglas
 * Date:        03/11/2017
 * Description: This is the header file for the Input class
 */

#ifndef FINAL_PROJECT_INPUT_HPP
#define FINAL_PROJECT_INPUT_HPP

#include <vector>
#include <functional>
#include <thread>
#include <chrono>
#include <atomic>

// The input class retrieves input from the keyboard without echoing it to terminal.  It uses multi-threading if available
// else it expects to be called on to check for new input.
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
    bool multi_threading = true;
    bool stop_trigger;
    void loop();
public:
    Input();
    ~Input();

    void listenTo(char c, v_d_callback callback);

    void getInput();
    void stop();
    void end();
    bool listen();

    bool is_multi_threading_enabled() { return multi_threading; }
    void disable_multi_threading(bool b);
};

#endif //FINAL_PROJECT_INPUT_HPP
