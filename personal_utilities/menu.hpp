/**
 * Author:          Brennan Douglas
 * Date:            03/05/2017
 * Description:     An object oriented way of creating a menu.
 *                  Menu class header file.
 */

#ifndef DOUGLBRE_PERSONAL_UTILITES_MENU_HPP
#define DOUGLBRE_PERSONAL_UTILITES_MENU_HPP

#include <vector>
#include <string>

// This class creates a command line menu with a variable number of options.
class Menu {
private:
    std::vector<std::string> titles;
    std::string menu_title;
public:
    Menu(std::string menu_title);
    Menu(std::string menu_title, std::string *titles, int size);
    Menu(std::string menu_title, std::vector<std::string> titles);
    Menu(const Menu &obj);
    ~Menu();
    void setTitle(std::string menu_title);
    int add(std::string title);
    int display();
    int quit();
};

#endif //DOUGLBRE_PERSONAL_UTILITES_MENU_HPP
