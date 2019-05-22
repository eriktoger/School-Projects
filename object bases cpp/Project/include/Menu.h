/**

@file Menu.h
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Definition of Jukebox
*/
#ifndef DT019G_MENU_H
#define DT019G_MENU_H

#include "MenuItem.h"
#include <vector>

class Menu {
private:
    std::vector <MenuItem> menu;
    std::string headline;
public:

    /**
    set headline
     @param newHeadline
    */
    void setHeadline(const std::string &newHeadline);

    /**
    add menu-item to menu
     @param newMenutext
     @param newEnable
    */
    void addItem(std::string newMenutext, bool newEnable);

    /**
    print all menu items
    */
    void printMenuItems();

    /**
    get menu choice
    @return choice
    */
    int getMenuChoice();

    /**
    get menu
    @return menu
    */
    std::vector <MenuItem> getMenu();

    /**
    enables menu
    */
    void enable();
};

#endif //DT019G_MENU_H
