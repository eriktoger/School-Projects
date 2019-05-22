/**

@file Jukebox.cpp
@author Erik Töger ertg1700
@date March 2019
@version: 1
@brief Implementation of Jukebox
*/

#include <iostream>
#include "Jukebox.h"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
/*
int main() {

    Jukebox jukebox;
    jukebox.run();

    Time test;
    test.setHours(30);
    test.setMinutes(30);
    test.setSeconds(30);
    Time test2;
    test2.setHours(45);
    test2.setMinutes(45);
    test2.setSeconds(45);
    test = test + test2;
    std::cout << test.getHours()<< " "<<test.getMinutes() << " " <<test.getSeconds()<<std::endl;

    return 0;
}
*/

/*
 * use shuffle to create random unique numbers
 * */