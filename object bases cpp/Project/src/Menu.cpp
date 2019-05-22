/**

@file Menu.cpp
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Implementation of Menu
*/
#include "Menu.h"
#include "constants.h"
#include <iostream>

//set headline
void Menu::setHeadline(const std::string &newHeadline){
    headline = newHeadline;
}

//add menu-item to menu
void Menu::addItem(std::string newMenutext, bool newEnable){
    MenuItem menuItem(newMenutext,newEnable);
    menu.push_back(menuItem);
}

//print all menu items
void Menu::printMenuItems(){

    std::cout << STARS<< " " << headline << " "<< STARS<<std::endl;
    int index = 1;

    for(auto const &menuitem : menu){
        std::cout << index << DOT_SPACE << menuitem.getMenutext() << std::endl;
        index++;

    }
}

//get menu choice
int Menu::getMenuChoice() {

    int choice = -1;
    bool enable = false;
    int long menuSize = menu.size();
    while(!enable){
        std::cout << "My choice: ";
        std::cin >> choice;
        if( choice > 0 && choice <= menuSize ){
            enable = menu[choice-1].getEnable();
        }

        if( !std::cin.good()){
            std::cin.clear();
            std::cin.ignore(999, '\n');
            choice = -1;
        }
    }

    return choice;
}

//get menu
std::vector <MenuItem> Menu::getMenu(){
    return menu;
}

//enables menu
void Menu::enable(){
    for (MenuItem &mi : menu){
        mi.setEnable(true);
    }
}