/**

@file MenuItem.cpp
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Implementation of MenuItem
*/

#include "MenuItem.h"
#include <iostream>
#include <string>

// Constructor
MenuItem::MenuItem(const std::string &newMenutext,const bool &newEnable){
    menutext = newMenutext;
    enable = newEnable;
}

//get menutext
std::string MenuItem::getMenutext() const {
    return menutext;
}

//get enable
bool MenuItem::getEnable() {
    return enable;
}

//set enable
void MenuItem::setEnable( bool newEnable) {
    enable = newEnable;
}