/**

@file MenuItem.h
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Definition of MenuItem
*/
#ifndef DT019G_MENUITEM_H
#define DT019G_MENUITEM_H


#include <string>

class MenuItem {
private:
    std::string menutext;
    bool enable;
public:
    /**
    Constructor
     @param newMenutext
     @param newEnable
    */
    MenuItem(const std::string &newMenutext,const bool &newEnable);

    /**
    get menutext
    @return menutext
    */
    std::string getMenutext() const;

    /**
    get enable
    @return if menuitem is enable
    */
    bool getEnable();

    /**
    set enable
    @param newEnable
    */
    void setEnable(bool newEnable);
};


#endif //DT019G_MENUITEM_H
