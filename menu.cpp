/**
 * Author:          Brennan Douglas
 * Date:            03/05/2017
 * Description:     An object oriented way of creating a menu.
 *                  Menu class source code file.
 */

#include "menu.hpp"
#include <iostream>
#include <vector>
#include <string>

// Basic constructor
Menu::Menu(std::string menu_title) {
    this->menu_title = menu_title;
}

// Array constructor
Menu::Menu(std::string menu_title, std::string *titles, int size) : Menu(menu_title) {
    for(int i = 0; i < size; i++) {
        this->titles.push_back(titles[i]);
    }
}

// Vector constructor
Menu::Menu(std::string menu_title, std::vector <std::string> titles) : Menu(menu_title) {
    this->titles = titles;
}

// Copy constructor
Menu::Menu(const Menu &obj) {
    this->titles = obj.titles;
    this->menu_title = obj.menu_title;
}

// Deconstructor
Menu::~Menu() {}

// Change the menu title
void Menu::setTitle(std::string menu_title) {
    this->menu_title = menu_title;
}

// Add an option to the menu
int Menu::add(std::string title) {
    titles.push_back(title);
    return (int) titles.size();
}

// Returns the value that represents the users wishing to quit the menu
int Menu::quit() {
    return (int) titles.size() + 1;
}

// Display the menu and ask for user input, selected option is returned
int Menu::display() {
    int size = (int) titles.size();
    std::string s_input;
    int input;
    std::cout << std::endl;
    do {
        input = 0;
        std::cout << menu_title << std::endl;
        for(int i = 0; i < size + 1; i++) {
            if(i == size) {
                std::cout << "  (" << i + 1 << ") Quit" << std::endl;
            } else {
                std::cout << "  (" << i + 1 << ") " << titles[i] << std::endl;
            }
        }
        std::cout << "  Select option: ";
        std::cin >> s_input;
        try {
            input = std::stoi(s_input);
            std::cin.ignore(100000, '\n');
            if (input > 0 && input <= size + 1) {
                return input;
            } else {
                std::cout << "That was not an option please try again." << std::endl << std::endl;
            }
        } catch ( std::exception e ) {
            std::cerr << "Invalid input, please input the integer of one of the options." << std::endl;
        }
    } while(input <= 0 || input > size);

    return -1;
}