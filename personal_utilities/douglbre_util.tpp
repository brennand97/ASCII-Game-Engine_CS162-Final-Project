/***********************************************************************
 * Author:       Brennan Douglas
 * Date:         01/15/2017
 * Description:  This is the template implementation file/pseudo-header
 *               where all the templated functions are defined.
 * ********************************************************************/

#ifdef DOUGLBRE_UTIL_HPP

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

namespace douglbre {
    namespace user {
        // This function will continully prompt the user with the prompt until their given input
        // is validated by the provided vaild function.  It the the vaild functions responsiblity
        // to print out what was wrong with the input and ask for a new value.
        template <class T> void validate_input(std::string prompt, T* input, std::function<bool(T)> valid) {
            bool noneNull;
            do {
                noneNull = false;
                std::cout << prompt << std::flush;

                if(std::cin >> (*input)) {
                    noneNull = true;
                    std::cin.clear();
                    std::cin.ignore(1000000000, '\n');
                } else {
                    std::cerr << "Invalid input, please try again." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1000000000, '\n');
                }

            } while (!noneNull || !valid(*input));
        }
    }

    namespace util {

    }
}

#endif