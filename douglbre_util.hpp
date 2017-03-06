/***********************************************************************
 * Author:       Brennan Douglas
 * Date:         01/15/2017
 * Description:  This is the header file for all my personal
 *               utility functions.
 * ********************************************************************/

#ifndef DOUGLBRE_UTIL_HPP
#define DOUGLBRE_UTIL_HPP

#include "douglbre_util.hpp"

#include <string>
#include <functional>

namespace douglbre {
    using v_v_callback = std::function<void()>;

    // The "user" namespace is meant for user related functions
    namespace user {
        bool string_validation(std::string a);

        void menu_loop(std::string menu_title, std::string* titles, v_v_callback* callbacks, int size);
        void menu_single(std::string menu_title, std::string* titles, v_v_callback* callbacks, int size);
        template <class T> void validate_input(std::string prompt, T* input, std::function<bool(T)> valid);
        template <> void validate_input<std::string>(std::string prompt, std::string* input, std::function<bool(std::string)> valid);
    }

    // The "util" namespace is meant for general utility functions
    namespace util {
        double rand_clamp(double min, double max);
        std::string* split_string(std::string str, std::string delim, std::size_t* out_size);
    }

    // The 'visual' namespace is meant for text visual helper functions
    namespace visual {
        std::string compressed_bar_graph(double *data, int data_size, int height, int bar_width, char value, char none_value);
    }
}

#include "douglbre_util.tpp"

#endif //DOUGLBRE_UTIL_HPP
